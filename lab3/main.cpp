#include "lab3.hpp"

int main() {
    const char path[] = "/home/hacker/prog/my_os_labs/build/lab3/child";
/*    std::ifstream in("infile.txt");


    if (!in.is_open()) {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }

    ParentRoutine(path, in);
    */
    ParentRoutine(path);
    exit(EXIT_SUCCESS);
}


/*#include "lab3.hpp"

int main() {

    std::vector<std::string> input = {
        "f1",
        "f2",
        "002",  
    };
    std::ofstream inFile("infile.txt");
    for (std::string line : input) {
        inFile << line << std::endl;
    }

    std::streambuf* oldInBuf = std::cin.rdbuf(inFile.rdbuf());

    const char path[] = "/home/hacker/prog/my_os_labs/build/lab3/child";
    ParentRoutine(path);
    std::cin.rdbuf(oldInBuf);
    std::cout << "aaaaaaa" <<std::endl;
    inFile.close();
    std::ifstream inFile1("infile.txt");

    if (inFile1.is_open()) {
        std::string line;
        while (std::getline(inFile1, line)) {
            std::cout << line << std::endl;
        }
        inFile1.close();
    }

    exit(EXIT_SUCCESS);
}*/