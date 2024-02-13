#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "utils.hpp"

#ifdef __cplusplus
extern "C" {
#endif

int PrimeCount(int a, int b);
int * Sort(int * array, int size);
void Swap(int* a, int* b);
int Partition(int * array, int low, int high);
void Quicksort(int * array, int low, int high);

#ifdef __cplusplus
}
#endif