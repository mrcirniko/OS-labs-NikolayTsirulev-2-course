#include "utils.hpp"

int main() {
    const char pathToLib1[] = "/home/hacker/prog/my_os_labs/build/lab4/lib1.so";
    const char pathToLib2[] = "/home/hacker/prog/my_os_labs/build/lab4/lib2.so";

    void* libraryHandle = LoadLibrary(pathToLib1);
    SortFunc Sort = (SortFunc)dlsym(libraryHandle, "Sort");
    PrimeCountFunc PrimeCount = (PrimeCountFunc)dlsym(libraryHandle, "PrimeCount");

    std::string command;
    while(true) {
        std::cout << "Enter the command (0 - switch realization, e - exit): ";
        std::cin >> command;
        if (command == "e") {
            break;
        } else if (command == "0") {
            std::cout << "Enter the library (1 or 2): ";
            std::cin >> command;
            if (command == "1") {
                libraryHandle = LoadLibrary(pathToLib1);
            } else if (command == "2") {
                libraryHandle = LoadLibrary(pathToLib2);
            } else {
                std::cout << "Invalid library" << std::endl;
            }
            Sort = (SortFunc)dlsym(libraryHandle, "Sort");
            PrimeCount = (PrimeCountFunc)dlsym(libraryHandle, "PrimeCount");
        } else {
            if (command == "1") {
                std::cout << "Sort function:" << std::endl;
                int arg1;
                std::cin >> arg1;
                //int arg2[arg1];
                int* arg2 = new int[arg1];
                for (int i = 0; i < arg1; ++i) {
                    std::cin >> arg2[i];
                }
                Sort(arg2, arg1);
                std::cout << "Result of sort = ";
                for (int i = 0; i < arg1; ++i) {
                    std::cout << arg2[i] << " ";
                }
                std::cout << std::endl;
            } else if (command == "2") {
                std::cout << "PrimeCount function:" << std::endl;
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                int result = PrimeCount(arg1, arg2);
                std::cout << "Count of prime numbers = " << result << std::endl;
            } else {
                std::cout << "Invalid command" << std::endl;
            }
        }
    }
    UnloadLibrary(libraryHandle);
    return 0;
}
