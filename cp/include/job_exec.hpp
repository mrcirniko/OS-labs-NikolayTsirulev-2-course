#pragma once

#include <iostream>
#include <optional>

#include <unistd.h>
#include <sys/wait.h>

#include "job_dag.hpp"

namespace cp {

class TSystem {
public:
    static int Exec(const std::string& path);
};

struct LogStack {
    // Stack of completed jobs
    std::vector<std::string> completed;
    size_t wasRead = 0;

    void Push(const std::string &str);

};

class TBasicExecutor {
private:
    LogStack * log;

public:

    void Execute(const std::string &name, const std::string &path, LogStack *log);
    TBasicExecutor(LogStack *_log) : log(_log) { }

};

class TDagJobExecutor {
private:

    size_t target, current;

    std::set<std::string> actuallyReadyToBeExecuted;

    LogStack log;
    TBasicExecutor ex;

public:

    TDagJobExecutor() : ex(&log) { }

    bool Execute(TJobDag &dag);

};

}
