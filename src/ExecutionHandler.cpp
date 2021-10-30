#include "../include/ExecutionHandler.hpp"


void execute(std::map<std::string, std::string> treestream) {
    std::map<std::string, short int> intVars;

    if (treestream.count("CALLED")) {
        if (treestream["CALLED"] == "OUT") {
            std::cout << treestream["VALUE"] << std::endl;
        }
    } else if (treestream.count("DECLARED")) {
        if (treestream["DECLARED"] == "INT_VAR") {
            std::stringstream ss(treestream["VALUE"]);
            ss >> intVars[treestream["KEY"]];
        }
    }
}
