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

    bool parenCheck = false;
    bool outCalled = false;
    bool openParen = false;
    bool closedParen = false;
    unsigned int lineNum = 0;
    bool end = false;
    std::string lastToken;
    bool openQuote = false;
    bool closedQuote = false;
    token curTreeVal;
    std::string string = "";

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
                    if (!(openParen)) {
                        if (it -> first == "OPEN_P")  {
                            openParen = true;
                        }
                    } else {
                        if (it -> first == "OPEN_P") {
                            this -> exit_err("ERROR: Too many parenthesis on line: " + std::to_string(lineNum));
                        } else if (it -> first == "CLOSED_P") {
                            closedParen = true;
                            parenCheck = false;
                        }
                    }
                }

                if (it -> first == "QUOTE" && !(openQuote)) {
                } else if (it -> first == "QUOTE" && openQuote) {
                    closedQuote = true;
                } else if (it -> first != "QUOTE" && openParen && !(closedParen)) {
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

        if (outCalled && !(openParen)) {
            this -> exit_err("ERROR: Missing parenthesis on line: " + std::to_string(lineNum));
        } else if (end && lastToken != "STATEMENT_END" && lastToken != "") {
            this -> exit_err("ERROR: Unexpected token on line: " + std::to_string(lineNum));
        } else if (!(end)) {
            this -> exit_err("ERROR: Missing semicolen on line: " + std::to_string(lineNum));
        } else if (openQuote && !(closedQuote) || !(openQuote) && closedQuote) {
            this -> exit_err("ERROR: Lingering quotes on line: " + std::to_string(lineNum));
        } else if (openParen && !(closedParen) || !(openParen) && closedParen) {
            this -> exit_err("ERROR: Lingering parenthesis on line: " + std::to_string(lineNum));
        }

        parenCheck = false;
        outCalled = false;
        openParen = false;
        closedParen = false;
        end = false;
        string = "";
        curTreeVal.clear();
    }

    return tree;
}
