#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <atomic>

struct Args {
    size_t ind = 0;
    size_t permsPerThread = 0;
    std::atomic<size_t> * sum = nullptr;
    const std::vector<std::vector<int> >* matrix = nullptr;
    const std::vector<std::vector<int> >* permutations = nullptr;

};

int calculatePermSign(const std::vector<int>& indices);
void *task(void *input);
int calculateDeterminant(size_t threadQuantity, const std::vector<std::vector<int>>& matrix);