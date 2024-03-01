#include "job_exec.hpp"

#include <atomic>

namespace cp {

int TSystem::Exec(const std::string& path) {
    int pid = fork();
    if (pid == 0) {
        if (execl(path.c_str(), path.c_str(), nullptr) == -1) {
            std::cout << "Can't exec: " << path <<'\n';
        }
    } else if (pid == -1) {
        throw std::logic_error("Can't fork");
    } else {
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
    return 0;
}

void LogStack::Push(const std::string &str) {
    completed.push_back(str);
}

void TBasicExecutor::Execute(const std::string &name, const std::string &path, LogStack *log) {
    try {
        int status = TSystem::Exec(path);
        if (status != 0) {
            exit(EXIT_FAILURE);
        }
    } catch (...) {
        exit(EXIT_FAILURE);
    }

    log->Push(name); // Warn about task completed
}

bool TDagJobExecutor::Execute(TJobDag &dag) {
    target = dag.jobs.size();
    current = 0;
    if (target == 0) {
        return true;
    }

    std::set<std::string_view> executionQueue;
    for (const auto& p : dag.jobs) {
        executionQueue.insert(p.first);
    }
    std::map<std::string_view, int> countOfDeps;
    for (const auto& p : dag.dep) {
        countOfDeps[p.first] = p.second.size();
    }

    // First layer
    for (const auto& p : dag.jobs) {
        if (countOfDeps[p.first] == 0) {
            actuallyReadyToBeExecuted.insert(p.first);
            executionQueue.erase(p.first);
        }
    }
    while (true) {
        if (current == target) {
            return true;
        } else {
            {
                std::vector<std::string> toErase;
                for (const auto& job : actuallyReadyToBeExecuted) {
                    toErase.push_back(job);
                    ex.Execute(job, dag.jobs[job].path, &log);

                }
                for (const auto& job : toErase) {
                    actuallyReadyToBeExecuted.erase(job);
                }
            }
            std::vector<std::string> completed;
            {
                for (size_t i = log.wasRead; i < log.completed.size(); i++) {
                    completed.push_back(log.completed[i]);
                    current++;
                }
                log.wasRead = log.completed.size();
            }
            for (const auto& job : completed) {
                for (const auto& depend : dag.rdep[job]) {
                    countOfDeps[depend]--;
                    if (countOfDeps[depend] == 0) {
                        actuallyReadyToBeExecuted.insert(depend);
                        executionQueue.erase(depend);
                    }
                }
            }

        }
    }
}



}
