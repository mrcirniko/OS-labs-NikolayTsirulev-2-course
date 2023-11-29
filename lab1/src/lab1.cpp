#include "lab1.hpp"
#define MODE (0644U)

int ParentRoutine(const char *pathToChild) {

    std::string fileName1;
    std::string fileName2;
    getline(std::cin, fileName1);
    getline(std::cin, fileName2);

    int fd1[2] {-1, -1};//pipe1
    int fd2[2] {-1, -1};//pipe2
    int fd[2] {-1, -1};
    createPipe(fd1);
    createPipe(fd2);
    fd[0] = open(fileName1.c_str(), O_CREAT | O_WRONLY | O_TRUNC, MODE);
    fd[1] = open(fileName2.c_str(), O_CREAT | O_WRONLY | O_TRUNC, MODE);

    pid_t pid[2] {-1, -1};
    pid[0] = createChildProcess();
    pid[1] = createChildProcess();

    if (pid[0] == 0) {//child 1
        close(fd2[0]);
        close(fd2[1]);
        close(fd1[1]);
        close(fd[1]);
        

        if (dup2(fd1[0], STDIN_FILENO) == -1) {
            perror("Error with dup2");
            exit(EXIT_FAILURE);
        }

        dup2(fd[0], STDOUT_FILENO);
        close(fd[0]);
        
        close(fd1[0]);
        if (execl(pathToChild, "child", nullptr) == -1) {
            perror("Error with execl");
            exit(EXIT_FAILURE);
        }
        
    } else if (pid[1] == 0) {//child 2
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);
        close(fd[0]);

        if (dup2(fd2[0], STDIN_FILENO) == -1) {
            perror("Error with dup2");
            exit(EXIT_FAILURE);
        }

        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        close(fd2[0]);
        if (execl(pathToChild, "child", nullptr) == -1) {
            perror("Error with execlp");
            exit(EXIT_FAILURE);
        }
        
    } else {//parent
        close(fd1[0]);
        close(fd2[0]);
        close(fd[0]);
        close(fd[1]);
        std::string str;
        while (getline(std::cin, str)) {
            str += "\n";
            if (str.size() % 2 != 0) {
                write(fd1[1], str.c_str(), str.size());
            } else {
                write(fd2[1], str.c_str(), str.size());
            }
            str.clear();
        }
        close(fd1[1]);
        close(fd2[1]);
        
        int status;
        waitpid(pid[0], &status, 0);
        waitpid(pid[1], &status, 0);

    }
    return 0;
}
