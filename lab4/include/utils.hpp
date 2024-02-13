#include <iostream>
#include <cstdlib>
#include <dlfcn.h>

using SortFunc = int (*)(int *, int);
using PrimeCountFunc = int (*)(int, int);

void* LoadLibrary(const char *libraryName);
void UnloadLibrary(void* handle);