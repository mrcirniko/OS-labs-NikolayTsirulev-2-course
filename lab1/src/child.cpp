#include "utils.hpp"

int main(void) {
    std::string str;
    while (std::getline(std::cin, str)) {
        std::reverse(str.begin(), str.end());
        printf("%s\n", str.c_str());
    }
    
    exit(EXIT_SUCCESS);  
}
