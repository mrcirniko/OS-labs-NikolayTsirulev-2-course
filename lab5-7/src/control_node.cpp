#include "topology.hpp"
#include "socket.hpp"
    
int main() {

    //export PATH_TO_CLIENT="/home/hacker/prog/my_os_labs/build/lab5-7/server"

    std::string path = getenv("PATH_TO_CLIENT");
    Topology list;
    std::vector<zmq::socket_t> branches;
    std::set<int> not_available_nodes;
    zmq::context_t context;

    std::string command;

    while (true) {
        std::cin >> command;
        if (command == "create") {
            int nodeId, parentId;
            std::cin >> nodeId >> parentId;
            if (list.find(nodeId) != -1) {
                std::cout << "Error: Already exists" << std::endl;
            } else if (parentId == -1) {
                pid_t pid = fork();
                if (pid < 0) {
                    std::cout << "Can't create new process" << std::endl;
                    return -1;
                } else if (pid == 0) {
                    //execl(path.c_str(), path.c_str(), std::to_string(nodeId).c_str(), NULL);
                    if (execl(path.c_str(), path.c_str(), std::to_string(nodeId).c_str(), NULL)==-1) {
                        std::cout << "Error with execl" << std::endl;
                        perror("Error with execl");
                        exit(EXIT_FAILURE);
                    }
                    std::cout << "Can't execute new process" << std::endl;
                    return -2;
                }
                branches.emplace_back(context, ZMQ_REQ);
                branches[branches.size() - 1].set(zmq::sockopt::sndtimeo, 5000);
                bind(branches[branches.size()-1], nodeId);
            
                sendMessage(branches[branches.size() - 1], std::to_string(nodeId) + " pid");
                
                std::string reply = receiveMessage(branches[branches.size() - 1]);
                std::cout << reply << std::endl;
                list.insert(nodeId, parentId);

            } else if (list.find(parentId) == -1) {

                std::cout << "Error: Parent not found" << std::endl;

            } else {
                int branch = list.find(parentId);
                sendMessage(branches[branch], std::to_string(parentId) + "create " + std::to_string(nodeId));

                std::string reply = receiveMessage(branches[branch]);
                std::cout << reply << std::endl;
                list.insert(nodeId, parentId);
            }
        } else if (command == "exec") {
            std::string s;
            getline(std::cin, s);
            std::string execCommand;
            std::vector<std::string> tmp;
            std::string tmp1 = " ";
            for (size_t i = 1; i < s.size(); i++) {
                tmp1 += s[i];
                if (s[i] == ' ' || i == s.size() - 1) {
                    tmp.push_back(tmp1);
                    tmp1 = " ";
                }
            }
            if (tmp.size() == 2) {
                execCommand = "check";
            } else {
                execCommand = "add";
            }
            int destId = stoi(tmp[0]);
            int branch = list.find(destId);
            if (branch == -1) {
                std::cout << "There is no such node id" << std::endl;
            } else {
                if (execCommand == "check") {
                    sendMessage(branches[branch], tmp[0] + "check" + tmp[1]);
                
                } else if (execCommand == "add") {
                    std::string value;
                    sendMessage(branches[branch], tmp[0] + "add" + tmp[1] + " " + tmp[2]);
                }
                std::string reply = receiveMessage(branches[branch]);
                std::cout << reply << std::endl;
            }
        } else if (command == "kill") {
            int id;
            std::cin >> id;
            int branch = list.find(id);
            if (branch == -1) {
                std::cout << " Error: incorrect node id" << std::endl;
            } else {
                bool is_first = (list.getFirstId(branch) == id);
                sendMessage(branches[branch], std::to_string(id) + "kill");
                std::string reply = receiveMessage(branches[branch]);
                std::cout << reply << std::endl;
                not_available_nodes.merge(list.getSetOfChilds(id));
                list.erase(id);
                if (is_first) {
                    unbind(branches[branch], id);
                    branches.erase(branches.begin() + branch);
                }
            }
        } else if (command == "pingall") {
            for (size_t i = 0; i < branches.size(); ++i) {
                int first_node_id = list.getFirstId(i);
                sendMessage(branches[i], std::to_string(first_node_id) + " ping");

                std::string received_message = receiveMessage(branches[i]);
                std::istringstream reply(received_message);
                int node;
                while(reply >> node) {
                    std::cout << "list " << node << std::endl;
                    not_available_nodes.erase(node);
                }
            }
            if (not_available_nodes.empty()) {
                std::cout << "OK: -1" << std::endl;
            } else {
                std::cout << "OK: ";
                for (size_t i : not_available_nodes) {
                    std::cout << i << ' ';
                }
                std::cout << std::endl;
            }
        } else if (command == "exit") {
            for (size_t i = 0; i < branches.size(); ++i) {
                int firstNodeId = list.getFirstId(i);
                sendMessage(branches[i], std::to_string(firstNodeId) + " kill");
                std::string reply = receiveMessage(branches[i]);
                if (reply != "OK") {
                    std::cout << reply << std::endl;
                } else {
                    unbind(branches[i], firstNodeId);
                }
            }
            exit(0);
        } else {
            std::cout << "Not correct command" << std::endl;
        }
    }
}