#include "utils.hpp"

void createPipe(int fd[2]) {
    if (pipe(fd) == -1) {
        perror("Couldn't create pipe");
        exit(EXIT_FAILURE);
    }
}

pid_t createChildProcess() {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Couldn't create child process");
        exit(EXIT_FAILURE);
    }
    return pid;
}
