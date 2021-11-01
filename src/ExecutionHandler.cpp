#include "../include/ExecutionHandler.hpp"


void execute(std::map<std::string, std::string> treestream) {

    /* Vars here are just in case we need to use them when we cannot get them from the parser. */
    std::map<std::string, short int> intVars;
    std::map<std::string, std::string> stringVars;

    static bool canExecute = true;
    static bool wasTrue = false;

    #ifdef TREE_DUMP
    typedef std::map<std::string, std::string> ss_map;
    for (ss_map::const_iterator it = treestream.begin(); it != treestream.end(); ++it) {
        std::cout << "[" << it -> first << ": " << it -> second << "]" << std::endl;
    }

    std::cout << "\n" << std::endl;
    #endif

    if (treestream.count("FLAGS")) {
        if (treestream["FLAGS"] == "IF_STATEMENT") {

            if (std::regex_match(treestream["CONDITION"], std::regex("(\\d+==\\d+|\\w+==\\w+)"))) {
                std::smatch m;
                std::regex_search(treestream["CONDITION"], m, std::regex("^\\d+"));

                std::string operand_1;
                std::string operand_2;

                for (int i = 0; i < m.size(); ++i) {
                    operand_1 = m[i];
                }

                std::regex_search(treestream["CONDITION"], m, std::regex("\\d+$"));

                for (int i = 0; i < m.size(); ++i) {
                    operand_2 = m[i];
                }

                if (treestream.count("OPERAND_1_VAL")) {
                    operand_1 = treestream["OPERAND_1_VAL"];
                }

                if (treestream.count("OPERAND_2_VAL")) {
                    operand_2 = treestream["OPERAND_2_VAL"];
                }

                canExecute = operand_1 == operand_2;
                wasTrue = operand_1 == operand_2;
            } else if (std::regex_match(treestream["CONDITION"], std::regex("(\\d+<\\d+|\\w+<\\w+)"))) {
                std::smatch m;
                std::regex_search(treestream["CONDITION"], m, std::regex("^\\d+"));

                std::string operand_1;
                std::string operand_2;

                short int operand_1_int;
                short int operand_2_int;

                for (int i = 0; i < m.size(); ++i) {
                    operand_1 = m[i];
                }

                std::regex_search(treestream["CONDITION"], m, std::regex("\\d+$"));

                for (int i = 0; i < m.size(); ++i) {
                    operand_2 = m[i];
                }

                if (treestream.count("OPERAND_1_VAL")) {
                    operand_1 = treestream["OPERAND_1_VAL"];
                }

                if (treestream.count("OPERAND_2_VAL")) {
                    operand_2 = treestream["OPERAND_2_VAL"];
                }

                std::stringstream ss(operand_1);
                ss >> operand_1_int;
                ss = std::stringstream(operand_2);
                ss >> operand_2_int;

                canExecute = operand_1 < operand_2;
                wasTrue = operand_1 < operand_2;
            } else if (std::regex_match(treestream["CONDITION"], std::regex("(\\d+>\\d+|\\w+>\\w+)"))) {
                std::smatch m;
                std::regex_search(treestream["CONDITION"], m, std::regex("^\\d+"));

                std::string operand_1;
                std::string operand_2;

                short int operand_1_int;
                short int operand_2_int;

                for (int i = 0; i < m.size(); ++i) {
                    operand_1 = m[i];
                }

                std::regex_search(treestream["CONDITION"], m, std::regex("\\d+$"));

                for (int i = 0; i < m.size(); ++i) {
                    operand_2 = m[i];
                }

                if (treestream.count("OPERAND_1_VAL")) {
                    operand_1 = treestream["OPERAND_1_VAL"];
                }

                if (treestream.count("OPERAND_2_VAL")) {
                    operand_2 = treestream["OPERAND_2_VAL"];
                }

                std::stringstream ss(operand_1);
                ss >> operand_1_int;
                ss = std::stringstream(operand_2);
                ss >> operand_2_int;

                canExecute = operand_1 > operand_2;
                wasTrue = operand_1 > operand_2;
            }  else if (std::regex_match(treestream["CONDITION"], std::regex("(\\d+!=\\d+|\\w+!=\\w+)"))) {
                std::smatch m;
                std::regex_search(treestream["CONDITION"], m, std::regex("^\\d+"));

                std::string operand_1;
                std::string operand_2;

                short int operand_1_int;
                short int operand_2_int;

                for (int i = 0; i < m.size(); ++i) {
                    operand_1 = m[i];
                }

                std::regex_search(treestream["CONDITION"], m, std::regex("\\d+$"));

                for (int i = 0; i < m.size(); ++i) {
                    operand_2 = m[i];
                }

                if (treestream.count("OPERAND_1_VAL")) {
                    operand_1 = treestream["OPERAND_1_VAL"];
                }

                if (treestream.count("OPERAND_2_VAL")) {
                    operand_2 = treestream["OPERAND_2_VAL"];
                }

                std::stringstream ss(operand_1);
                ss >> operand_1_int;
                ss = std::stringstream(operand_2);
                ss >> operand_2_int;

                canExecute = operand_1 != operand_2;
                wasTrue = operand_1 != operand_2;
            }
        } else if (treestream["FLAGS"] == "ELSE") {
            if (!(wasTrue)) {
                canExecute = true;
            } else {
                canExecute = false;
            }
        }
    } else {
        wasTrue = false;
        canExecute = true;
    }

    if (canExecute) {
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
                    } else if (treestream["OPERATOR"] == "==") {
                        int operand_1;
                        int operand_2;

                        std::stringstream ss;
                        ss << treestream["OPERAND_1"];
                        ss >> operand_1;
                        boost::trim(treestream["OPERAND_2"]);
                        ss = std::stringstream(treestream["OPERAND_2"]);
                        ss >> operand_2;

                        if (operand_1 == operand_2) {
                            std::cout << "true" << std::endl;
                        } else {
                            std::cout << "false" << std::endl;
                        }
                    } else if (treestream["OPERATOR"] == "!=") {
                        int operand_1;
                        int operand_2;

                        std::stringstream ss;
                        ss << treestream["OPERAND_1"];
                        ss >> operand_1;
                        boost::trim(treestream["OPERAND_2"]);
                        ss = std::stringstream(treestream["OPERAND_2"]);
                        ss >> operand_2;

                        if (operand_1 != operand_2) {
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
            } else if (treestream["DECLARED"] == "STRING_VAR") {
                stringVars[treestream["KEY"]] = treestream["VALUE"];
            }
        } else if (treestream.count("OPERATOR")) {
            if (treestream["OPERATOR"] == "PRE-INCREMENT") {
                ++intVars[treestream["KEY"]];
            }
        }
    }
}
