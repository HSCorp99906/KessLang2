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

    token curTreeVal;
    std::string string = "";

    short_uint openParenCount = 0;
    short_uint closedParenCount = 0;

    for (int i = 0; i < this -> tokens.size(); ++i) {
        for (int j = 0; j < this -> tokens[i].size(); ++j) {
            for (token::const_iterator it = this -> tokens[i][j].begin(); it != tokens[i][j].end(); ++it) {
                if (it -> second == "out") {
                    parenCheck = true;
                    outCalled = true;
                } else if (it -> first == "STATEMENT_END") {
                    end = true;
                }

                if (parenCheck) {
                    if (it -> first == "OPEN_P") {
                        ++openParenCount;
                    } else if (it -> first == "CLOSED_P") {
                        ++closedParenCount;
                    }
                }

                if (it -> first == "QUOTE" && !(openQuote)) {
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
            curTreeVal["CALLED"] = "OUT";
            curTreeVal["STRING"] = string;
            this -> tree.push_back(curTreeVal);
        }

        if (outCalled && openParenCount == 0 && closedParenCount == 0) {
            this -> exit_err("ERROR: Missing parenthesis on line: " + std::to_string(lineNum));
        } else if (end && lastToken != "STATEMENT_END" && lastToken != "") {
            this -> exit_err("ERROR: Unexpected token on line: " + std::to_string(lineNum));
        } else if (!(end)) {
            this -> exit_err("ERROR: Missing semicolen on line: " + std::to_string(lineNum));
        } else if (openQuote && !(closedQuote) || !(openQuote) && closedQuote) {
            this -> exit_err("ERROR: Lingering quotes on line: " + std::to_string(lineNum));
        } else if (openParenCount < closedParenCount || openParenCount > closedParenCount || closedParenCount < openParenCount || closedParenCount > openParenCount) {
            this -> exit_err("ERROR: Lingering parenthesis on line: " + std::to_string(lineNum));
        }

        parenCheck = false;
        outCalled = false;
        openParenCount = 0;
        closedParenCount = 0;
        end = false;
        string = "";
        curTreeVal.clear();
    }

    return tree;
}
