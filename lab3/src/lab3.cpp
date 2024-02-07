#include "lab3.hpp"

int ParentRoutine(const char *pathToChild) {
    std::string fileName1;
    std::string fileName2;
    
    getline(std::cin, fileName1);
    getline(std::cin, fileName2);

    sem_t* semptr1 = OpenSemaphore(EVEN_SEMAPHORE_NAME, 0);
    sem_t* semptr2 = OpenSemaphore(ODD_SEMAPHORE_NAME, 0);
    
    int shared_memory_fd1 = OpenSharedMemory(SHARED_MEMORY_NAME_1, MAP_SIZE);
    char *memptr1 = MapSharedMemory(MAP_SIZE, shared_memory_fd1);

    int shared_memory_fd2 = OpenSharedMemory(SHARED_MEMORY_NAME_2, MAP_SIZE);
    char *memptr2 = MapSharedMemory(MAP_SIZE, shared_memory_fd2);

    pid_t pid[2] {-1, -1};
    pid[0] = createChildProcess();
    pid[1] = createChildProcess();

    if (pid[0] == 0) {//child 1
        if (execl(pathToChild, "child", EVEN_SEMAPHORE_NAME, SHARED_MEMORY_NAME_1, fileName1.c_str(), nullptr) == -1) {
            perror("Error with execl");
            exit(EXIT_FAILURE);
        }
        
    } else
    if (pid[1] == 0) {//child 2
        if (execl(pathToChild, "child", ODD_SEMAPHORE_NAME, SHARED_MEMORY_NAME_2, fileName2.c_str(), nullptr) == -1) {
            perror("Error with execl");
            exit(EXIT_FAILURE);
        }
        
    } else {//parent
        std::string str;
        while (getline(std::cin, str)) {
            std::chrono::milliseconds delay(10);
            std::this_thread::sleep_for(delay);
            
            if (str.size() % 2 == 0) {
                strcpy(memptr1, str.c_str());
                sem_post(semptr1);
            } else {
                strcpy(memptr2, str.c_str());
                sem_post(semptr2);
            }
            str.clear();
        }
        std::chrono::milliseconds delay(10);
        std::this_thread::sleep_for(delay);

        strcpy(memptr1, "\0");
        sem_post(semptr1);
        strcpy(memptr2, "\0");
        sem_post(semptr2);

        int status;
        waitpid(pid[0], &status, 0);
        waitpid(pid[1], &status, 0);

        sem_close(semptr1);
        sem_unlink(EVEN_SEMAPHORE_NAME);
        shm_unlink(SHARED_MEMORY_NAME_1);
        munmap(memptr1, MAP_SIZE);
        close(shared_memory_fd1);

        sem_close(semptr2);
        sem_unlink(ODD_SEMAPHORE_NAME);
        shm_unlink(SHARED_MEMORY_NAME_2);
        munmap(memptr2, MAP_SIZE);
        close(shared_memory_fd2);
    }
    return 0;
}