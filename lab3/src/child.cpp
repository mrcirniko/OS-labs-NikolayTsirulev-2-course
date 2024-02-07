#include "utils.hpp"

int main(int argc, char* argv[]) {
    (void)argc;
    
    sem_t *semptr = OpenSemaphore(argv[1], 0);
    int shared_memory_fd = OpenSharedMemory(argv[2], MAP_SIZE);
    char *memptr = MapSharedMemory(MAP_SIZE, shared_memory_fd);
    std::ofstream fout(argv[3],  std::ios::trunc);
    fout.close();

    while (true) {
        sem_wait(semptr);
        std::string_view st(memptr);
        std::string str = {st.begin(), st.end()};
        if (str == "\0") {
            break;
        }
        std::reverse(str.begin(), str.end());
        std::ofstream fout(argv[3],  std::ios::app);
        if (!fout.is_open()) {
            perror("Couldn't open the file");
            exit(EXIT_FAILURE);
        }
        fout << str << std::endl;
        fout.close();
    }
    sem_close(semptr);
    sem_unlink(argv[1]);
    shm_unlink(argv[2]);
    munmap(memptr, MAP_SIZE);
    close(shared_memory_fd);
    exit(EXIT_SUCCESS);
}