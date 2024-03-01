#include "gtest/gtest.h"

#include "job_exec.hpp"

std::string getPath() {
    
    // export PATH_TO_EX_DIR="/home/hacker/prog/my_os_labs/data/cp/"

    if (getenv("PATH_TO_EX_DIR") == nullptr) {
        std::cout << "PATH_TO_EX_DIR is not specified\n";
        exit(EXIT_FAILURE);
    }
    std::string path = std::string(getenv("PATH_TO_EX_DIR"));
    return path;
}

TEST(CP, Test1) {
    std::string path = getPath() + "ex1/ex1.json";
    std::cout << path << std::endl;
    cp::TJobDag dag = cp::JSONParser::Parse(path);
    cp::TDagJobExecutor ex;
    EXPECT_TRUE(ex.Execute(dag));
}

TEST(CP, Test2) {
    std::string path = getPath() + "ex2/ex2.json";
    cp::TJobDag dag = cp::JSONParser::Parse(path);
    cp::TDagJobExecutor ex;
    ex.Execute(dag);
    EXPECT_TRUE(ex.Execute(dag));
}

TEST(CP, Test3) {
    std::string path = getPath() + "ex3/ex3.json";
    EXPECT_THROW({cp::TJobDag dag = cp::JSONParser::Parse(path);}, std::logic_error);
}

