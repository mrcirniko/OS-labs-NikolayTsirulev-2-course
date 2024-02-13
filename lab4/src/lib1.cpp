#include "lib.hpp"

extern "C" int PrimeCount(int a, int b) {
    int count = 0;
    bool flag = true;
    for (int i = a; i <= b; ++i) {
        if (i <= 1) {
            continue;
        }
        for (int j = 2; j < i; ++j) {
            if (i % j == 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ++count;
        }
        flag = true;
    }
    return count;
}

extern "C" void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//bubble
extern "C" int * Sort(int * array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                Swap(&array[j], &array[j + 1]);
            }
        }
    }

    return array;
}