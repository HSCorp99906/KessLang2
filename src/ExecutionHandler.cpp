#include "../include/ExecutionHandler.hpp"


void execute(std::map<std::string, std::string> treestream) {
    std::map<std::string, short int> intVars;

    #ifdef TREE_DUMP
    typedef std::map<std::string, std::string> ss_map;
    for (ss_map::const_iterator it = treestream.begin(); it != treestream.end(); ++it) {
        std::cout << "[" << it -> first << ": " << it -> second << "]" << std::endl;
    }

    std::cout << "\n" << std::endl;
    #endif

    if (treestream.count("CALLED")) {
        if (treestream["CALLED"] == "OUT") {
            if (treestream["VALUE"] != "__OPERATOR__") {
                std::cout << treestream["VALUE"] << std::endl;
            } else {
                if (treestream["OPERATOR"] == "<") {
                    int operand_1;
                    int operand_2;

                    std::stringstream ss;
                    ss << treestream["OPERAND_1"];
                    ss >> operand_1;
                    boost::trim(treestream["OPERAND_2"]);
                    ss = std::stringstream(treestream["OPERAND_2"]);
                    ss >> operand_2;

                    if (operand_1 < operand_2) {
                        std::cout << "true" << std::endl;
                    } else {
                        std::cout << "false" << std::endl;
                    }
                } else if (treestream["OPERATOR"] == ">") {
                    int operand_1;
                    int operand_2;

                    std::stringstream ss;
                    ss << treestream["OPERAND_1"];
                    ss >> operand_1;
                    boost::trim(treestream["OPERAND_2"]);
                    ss = std::stringstream(treestream["OPERAND_2"]);
                    ss >> operand_2;

                    if (operand_1 > operand_2) {
                        std::cout << "true" << std::endl;
                    } else {
                        std::cout << "false" << std::endl;
                    }
                }
            }
        }
    } else if (treestream.count("DECLARED")) {
        if (treestream["DECLARED"] == "INT_VAR") {
            std::stringstream ss(treestream["VALUE"]);
            ss >> intVars[treestream["KEY"]];
        }
    } else if (treestream.count("OPERATOR")) {
        if (treestream["OPERATOR"] == "PRE-INCREMENT") {
            ++intVars[treestream["KEY"]];
        }
    }
}
