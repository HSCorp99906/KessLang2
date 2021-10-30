#include "../include/Parser.hpp"


Parser::Parser(__tokens tokens) {
    this -> tokens = tokens;
}


void Parser::exit_err(std::string message) {
    src.close();
    std::cout << message << std::endl;
    exit(1);
}


std::vector<std::map<std::string, std::string>> Parser::parse() {
    typedef std::map<std::string, std::string> token;
    typedef unsigned short int short_uint;

    bool parenCheck = false;
    bool outCalled = false;

    unsigned int lineNum = 0;
    bool end = false;
    std::string lastToken;

    bool openQuote = false;
    bool closedQuote = false;
    bool unexpectedToken = false;

    bool expectingIntVarKey = false;
    bool expectingIntVarValue = false;
    bool space = false;

    token curTreeVal;

    std::string string = "";
    std::string varKey = "";
    std::string varValue = "";

    bool varValueFound = false;
    bool invalidTypeInt = false;  // If what is supposed to be int has invalid type.
    bool varIntOverflow = false;
    bool varIntUnderflow = false;
    bool varLine = false;
    bool defined = false;
    bool varAlreadyExists = false;  // Raises error if var already exists.

    bool unsupportedFeatureUsed = false;
    bool varNotFound = false;
    bool lgOperator = false;
    bool equalityOperator = false;

    bool incrementUsed = false;

    short_uint openParenCount = 0;
    short_uint closedParenCount = 0;

    for (int i = 0; i < this -> tokens.size(); ++i) {
        for (int j = 0; j < this -> tokens[i].size(); ++j) {
            for (token::const_iterator it = this -> tokens[i][j].begin(); it != tokens[i][j].end(); ++it) {

                if (expectingIntVarKey && space) {
                    if (it -> first != "SPACE") {
                        varKey += it -> second;
                    } else {
                        expectingIntVarKey = false;
                        space = false;
                        curTreeVal["DECLARED"] = "INT_VAR";
                        expectingIntVarValue = true;
                        curTreeVal["KEY"] = varKey;
                    }
                } else if (expectingIntVarValue) {
                    if (it -> second == "=") {
                        defined = true;
                    }

                    if (it -> first != "STATEMENT_END") {
                        varValue += it -> second;
                    } else {
                        expectingIntVarValue = false;
                    }

                    if (!(expectingIntVarValue)) {
                        varValue = std::regex_replace(varValue, std::regex("="), "");
                        varValue = std::regex_replace(varValue, std::regex("`"), "");

                        if (std::regex_match(varValue, std::regex("\".*\""))) {
                            invalidTypeInt = true;
                        } else if (std::regex_match(varValue, std::regex("[A-Za-z]+[a-zA-Z0-9]*"))) {
                            unsupportedFeatureUsed = true;
                        } else if (std::regex_match(varValue, std::regex("\\d+\\.\\d+"))) {
                            invalidTypeInt = true;
                        }

                        if (this -> varsCopy.count(varKey)) {
                            varAlreadyExists = true;
                        }

                        if (!(varAlreadyExists) && !(invalidTypeInt) && !(unsupportedFeatureUsed)) {
                            std::stringstream ss(varValue);

                            int checkVal;

                            ss >> checkVal;

                            if (checkVal > 32764) {
                                varIntOverflow = true;
                            } else if (checkVal < -32764) {
                                varIntUnderflow = true;
                            }

                            this -> varsCopy[varKey] = varValue;

                            curTreeVal["VALUE"] = varValue;
                            this -> tree.push_back(curTreeVal);
                        }
                    }
                }

                if (incrementUsed) {
                    if (it -> first != "OPERATOR" && it -> first != "STATEMENT_END") {
                        varKey += it -> second;
                    }
                }

                if (it -> second == "++") {
                    incrementUsed = true;
                }

                if (it -> second == "out") {
                    parenCheck = true;
                    outCalled = true;
                } else if (it -> first == "STATEMENT_END" && !(end)) {
                    end = true;
                } else if (it -> first == "STATEMENT_END" && end) {
                    unexpectedToken = true;
                } else if (it -> first == "INT_VAR_DECLARATION") {
                    expectingIntVarKey = true;
                    varLine = true;
                } else if (it -> first == "SPACE") {
                    space = true;
                }

                if (parenCheck) {
                    if (it -> first == "OPEN_P") {
                        ++openParenCount;
                    } else if (it -> first == "CLOSED_P") {
                        ++closedParenCount;
                    }
                }

                if (it -> first == "QUOTE" && !(openQuote)) {
                    openQuote = true;
                } else if (it -> first == "QUOTE" && openQuote) {
                    closedQuote = true;
                } else if (it -> first != "QUOTE" && openParenCount > 0 && closedParenCount < 1) {
                    string += it -> second;
                }

                lastToken = it -> first;
            }
        }

        ++lineNum;

        if (outCalled) {
            string = std::regex_replace(string, std::regex("`"), " ");
            string = std::regex_replace(string, std::regex("\\("), "");

            if (!(this -> varsCopy.count(string)) && openQuote || std::regex_match(string, std::regex("\\d+")) || std::regex_match(string, std::regex("(true|false)"))) {
                curTreeVal["CALLED"] = "OUT";
                curTreeVal["VALUE"] = string;
                this -> tree.push_back(curTreeVal);
            } else if (this -> varsCopy.count(string)) {
                curTreeVal["CALLED"] = "OUT";
                curTreeVal["VALUE"] = this -> varsCopy[string];
                this -> tree.push_back(curTreeVal);
            } else {

                std::smatch m;

                curTreeVal["CALLED"] = "OUT";
                curTreeVal["VALUE"] = "__OPERATOR__";
                this -> tree.push_back(curTreeVal);

                std::regex_search(string, m, std::regex("(>|<|==|!=)"));

                for (int f = 0; f < m.size(); ++f) {
                    if (m[f] == '>' || m[f] == '<') {
                        lgOperator = true;
                        curTreeVal["OPERATOR"] = m[f];

                        std::regex_search(string, m, std::regex("^\\d+"));

                        for (int v = 0; v < m.size(); ++v) {
                            curTreeVal["OPERAND_1"] = m[v];
                        }

                        std::regex_search(string, m, std::regex("(<\\s*\\d+|>\\s*\\d+)"));

                        for (int v = 0; v < m.size(); ++v) {
                            std::string op2 = m[v];
                            op2 = std::regex_replace(op2, std::regex("<"), "");
                            op2 = std::regex_replace(op2, std::regex(">"), "");
                            op2 = std::regex_replace(op2, std::regex(" "), "");

                            curTreeVal["OPERAND_2"] = op2;
                        }
                    } else if (m[f] == "==") {
                        equalityOperator = true;
                        curTreeVal["OPERATOR"] = m[f];

                        std::regex_search(string, m, std::regex("^\\d+"));

                        for (int v = 0; v < m.size(); ++v) {
                            curTreeVal["OPERAND_1"] = m[v];
                        }

                        std::regex_search(string, m, std::regex("(==\\s*\\d+)"));

                        for (int v = 0; v < m.size(); ++v) {
                            std::string op2 = m[v];
                            op2 = std::regex_replace(op2, std::regex("=="), "");
                            op2 = std::regex_replace(op2, std::regex(" "), "");

                            curTreeVal["OPERAND_2"] = op2;
                        }
                    } else if (m[f] == "!=") {
                        equalityOperator = true;

                        curTreeVal["OPERATOR"] = m[f];

                        std::regex_search(string, m, std::regex("^\\d+"));

                        for (int v = 0; v < m.size(); ++v) {
                            curTreeVal["OPERAND_1"] = m[v];
                        }

                        std::regex_search(string, m, std::regex("(!=\\s*\\d+)"));

                        for (int v = 0; v < m.size(); ++v) {
                            std::string op2 = m[v];
                            op2 = std::regex_replace(op2, std::regex("!="), "");
                            op2 = std::regex_replace(op2, std::regex(" "), "");

                            curTreeVal["OPERAND_2"] = op2;
                        }
                    }
                }

                if (!(lgOperator) && !(equalityOperator)) {
                    varNotFound = true;
                } else {
                    this -> tree.push_back(curTreeVal);
                }
            }
        } else if (incrementUsed) {
            if (!(this -> varsCopy.count(varKey))) {
                varNotFound = true;
            } else {
                std::stringstream ss(this -> varsCopy[varKey]);
                int updateInt;
                ss >> updateInt;
                ++updateInt;
                this -> varsCopy[varKey] = std::to_string(updateInt);
                curTreeVal["OPERATOR"] = "PRE-INCREMENT";
                curTreeVal["KEY"] = varKey;
                this -> tree.push_back(curTreeVal);
            }
        }

        if (outCalled && openParenCount == 0 && closedParenCount == 0) {
            this -> exit_err("ERROR: Missing parenthesis on line: " + std::to_string(lineNum));
        } else if (end && lastToken != "STATEMENT_END" && lastToken != "") {
            this -> exit_err("ERROR: Unexpected token on line: " + std::to_string(lineNum));
        } else if (!(end)) {
            this -> exit_err("ERROR: Missing semicolen on line: " + std::to_string(lineNum));
        } else if (openQuote && !(closedQuote) || !(openQuote) && closedQuote) {
            this -> exit_err("ERROR: Lingering quotes on line: " + std::to_string(lineNum));
        } else if (openParenCount != closedParenCount) {
            this -> exit_err("ERROR: Lingering parenthesis on line: " + std::to_string(lineNum));
        } else if (unexpectedToken) {
            this -> exit_err("ERROR: Unexpected token on line: " + std::to_string(lineNum));
        } else if (varLine && !(defined)) {
            this -> exit_err("ERROR: Variable not defined on line: " + std::to_string(lineNum));
        } else if (invalidTypeInt) {
            this -> exit_err("ERROR: Invalid data used for type int on line: " + std::to_string(lineNum));
        } else if (unsupportedFeatureUsed) {
            this -> exit_err("ERROR: The feature you are trying to use is not supported. For now.. LINE: " + std::to_string(lineNum));
        } else if (varAlreadyExists) {
            this -> exit_err("ERROR: Variable re-declared on line: " + std::to_string(lineNum));
        } else if (varNotFound) {
            this -> exit_err("ERROR: Variable not found on line: " + std::to_string(lineNum));
        } else if (varIntOverflow) {
            this -> exit_err("ERROR: Integer overflow detected on line: " + std::to_string(lineNum));
        } else if (varIntUnderflow)  {
            this -> exit_err("ERROR: Integer underflow detected on line: " + std::to_string(lineNum));
        }

        parenCheck = false;
        outCalled = false;
        openParenCount = 0;
        closedParenCount = 0;
        end = false;
        space = false;
        lgOperator = false;
        unsupportedFeatureUsed = false;
        expectingIntVarKey = false;
        expectingIntVarValue = false;
        invalidTypeInt = false;
        varValueFound = false;
        varAlreadyExists = false;
        varLine = false;
        incrementUsed = false;
        equalityOperator = false;
        defined = false;
        string = "";
        varKey = "";
        varValue = "";
        curTreeVal.clear();
    }

    return this -> tree;
}
