#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <fcntl.h>
#include <sys/wait.h>

void createPipe(int fd[2]);
pid_t createChildProcess();
