#include "lib.hpp"

#include <iostream>

void Task(const std::string& command) {
    if (command == "1") {
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
        int arg1, arg2;
        std::cin >> arg1 >> arg2;
        int result = PrimeCount(arg1, arg2);
        std::cout << "Count of prime numbers = " << result << std::endl;
    } else {
        std::cout << "Invalid command" << std::endl;
    }
}

int main() {
    std::string command;
    while(true) {
        std::cout << "Enter the command (0 - exit): ";
        std::cin >> command;
        if (command == "0") {
            break;
        }
        Task(command);
    }
    return 0;
}