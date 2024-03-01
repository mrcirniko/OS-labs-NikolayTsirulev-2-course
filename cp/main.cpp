#include <iostream>
#include <fstream>

#include "nlohmann/json.hpp"

#include "job_dag.hpp"
#include "job_exec.hpp"

using json = nlohmann::json;
using namespace cp;

int main(int argc, char ** argv) {
    if (argc < 1) {
        std::cerr << "Missing arguments : path to config file\n";
        exit(EXIT_FAILURE);
    }
    
    std::string pathToConfig(argv[1]);
    TJobDag dag = JSONParser::Parse(pathToConfig);
    TDagJobExecutor executor;
    executor.Execute(dag);

    std::cout << "Execution finished!\n";
}