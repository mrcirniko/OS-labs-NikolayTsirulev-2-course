#include "lib.hpp"

extern "C" int PrimeCount(int a, int b) {
    int count = 0;
    std::vector<int> numbers;
    for (int i = 0; i <= b; ++i) {
        numbers.push_back(i);
    }
    for (int i = 2; i <= b; ++i) {
        if (numbers[i] != 0) {
            if (numbers[i] >= a && numbers[i] <= b) {
                ++count;
            }
            for (int j = i * i; j <= b; j += i) {
                numbers[j] = 0;
            }
        }
    }
    return count;
}
//qsort


extern "C" void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

extern "C" int Partition(int * array, int low, int high) {
    int pivot = array[(low + high) / 2];
    int i = low;
    int j = high;
    while(true) {
        while (array[i] < pivot) {
            ++i;
        }
        while (array[j] > pivot) {
            --j;
        }
        if (i >= j) {
           return j;
        }
        Swap(&array[i++], &array[j--]);
    }
}

extern "C" void Quicksort(int * array, int low, int high) {
    if (low < high) {
        int p = Partition(array, low, high);
        Quicksort(array, low, p);
        Quicksort(array, p + 1, high);
    }
}

extern "C" int * Sort(int * array, int size) {
    Quicksort(array, 0, size - 1);
    return array;
}