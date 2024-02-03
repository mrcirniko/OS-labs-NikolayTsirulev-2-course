#include <lab2.hpp>

size_t fact(size_t n) {
    if (n == 0) {
        return 1;
    }
    return n * fact(n - 1);
}

int calculatePermSign(const std::vector<int>& indices) {
    int numInversions = 0;
    int size = indices.size();
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (indices[i] > indices[j]) {
                numInversions++;
            }
        }
    }
    return numInversions % 2 == 0 ? 1 : -1;
}

void *task(void *input) {
    const auto &args = *(reinterpret_cast<Args *>(input));
    const std::vector<std::vector<int> >& perms = *(args.permutations);
    const std::vector<std::vector<int> >& mat = *(args.matrix);
    size_t partOfSum = 0;
    size_t startInd = args.ind * args.permsPerThread;
    size_t endInd = startInd + args.permsPerThread;

    for (size_t i = startInd; i < endInd; i++) {
        std::vector<int> indices = perms[i];
        int permSign = calculatePermSign(indices);
        int permSummand = 1;

        for(size_t j = 0; j < indices.size(); j++) {
            permSummand *= mat[j][indices[j]];
        }
        partOfSum += (permSign * permSummand);
    }
    (*args.sum).fetch_add(partOfSum);
    return nullptr;
}

int calculateDeterminant(size_t threadQuantity, const std::vector<std::vector<int>>& matrix) {
    size_t n = matrix.size();
    std::vector<int> indices(n);

    size_t number_of_perm = fact(n);
    if (number_of_perm % threadQuantity != 0) {
        perror("Incorrect number of threads. It must be integers divided by the factorial of the order of the matrix.");
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<int> > permutations(number_of_perm);
    int determinant{0};
    for(size_t i = 0; i < n; i++) {
        indices[i] = i;
    }
    for(size_t i = 0; i < permutations.size(); i++) {
        std::next_permutation(indices.begin(), indices.end());
        permutations[i] = indices;
    }
    if (threadQuantity > 1) {
        std::atomic<size_t> sum {0};
        const size_t actualThreadQuantity = std::min(threadQuantity, permutations.size());
        std::vector<pthread_t> threads(actualThreadQuantity);

        const size_t permsPerThread = permutations.size() / actualThreadQuantity;

        std::vector<Args> argsForThread(actualThreadQuantity);

        for (size_t i = 0; i < actualThreadQuantity; i++) {
            argsForThread[i].permsPerThread = permsPerThread;
            argsForThread[i].sum = &sum;
            argsForThread[i].matrix = &matrix;
            argsForThread[i].permutations = &permutations;
            argsForThread[i].sum = &sum;
            argsForThread[i].ind = i;

            pthread_create(&threads[i], nullptr, task, reinterpret_cast<void *>(&argsForThread[i]));
        }
        for (auto &thread : threads) {
            pthread_join(thread, nullptr);
        }
        determinant = (int)sum;
    } else {
        for (size_t i = 0; i < permutations.size(); i++) {
            int permSign = calculatePermSign(permutations[i]);
            int permSummand = 1;
            for(size_t j = 0; j < n; j++) {
                permSummand *= matrix[j][permutations[i][j]];
            }
            determinant += (permSign * permSummand);
        }
    }
    return determinant;
}