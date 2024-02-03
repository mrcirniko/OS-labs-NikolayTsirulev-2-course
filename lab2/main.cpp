#include <lab2.hpp>

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cout << "wrong arguments" << std::endl;
        return -1;
    }
    size_t threadQuantity = std::atol(argv[1]);
    std::vector<std::vector<int>> matrix = { 
            { 3, 6, 2, 9, 2 }, 
            { 5, 8, 3, 5, 2 }, 
            { 5, 4, 8, 10, 3 }, 
            { 1, 4, 7, 5, 5 }, 
            { 6, 9, 3, 1, 4 }
    };

    int determinant = calculateDeterminant(threadQuantity, matrix);
    
    std::cout << determinant << std::endl;
    return 0;
}