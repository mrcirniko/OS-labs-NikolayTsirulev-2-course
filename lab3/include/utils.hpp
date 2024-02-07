#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <utility>
#include <thread>
#include <chrono>

const int MAP_SIZE = 1024;

constexpr const char *EVEN_SEMAPHORE_NAME = "/even_semaphore";
constexpr const char *ODD_SEMAPHORE_NAME = "/odd_semaphore";
constexpr const char *EXIT_SEMAPHORE_NAME = "/exit_semaphore";

constexpr const char *SHARED_MEMORY_NAME_1 = "/shared_memory_1";
constexpr const char *SHARED_MEMORY_NAME_2 = "/shared_memory_2";


pid_t createChildProcess();
sem_t* OpenSemaphore(const char *name, int value);
int OpenSharedMemory(const char *name, const int size);
char* MapSharedMemory(const int size, int fd);
