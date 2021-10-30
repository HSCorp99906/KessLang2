#include "../include/ExecutionHandler.hpp"


void execute(std::map<std::string, std::string> treestream) {
    if (treestream.count("CALLED")) {
        if (treestream["CALLED"] == "OUT") {
            std::cout << treestream["STRING"] << std::endl;
        }
    }
}
