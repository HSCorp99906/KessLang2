#include "../include/ExecutionHandler.hpp"


void execute(std::map<std::string, std::string> treestream) {
    std::map<std::string, short int> intVars;

    #ifdef TREE_DUMP
    typedef std::map<std::string, std::string> ss_map;
    for (ss_map::const_iterator it = treestream.begin(); it != treestream.end(); ++it) {
        std::cout << "[" << it -> first << ": " << it -> second << "]" << std::endl;
    }
    #endif

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
