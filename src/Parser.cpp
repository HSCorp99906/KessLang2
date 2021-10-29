#include "../include/Parser.hpp"


Parser::Parser(__tokens tokens) {
    this -> tokens = tokens;
}


void Parser::exit_err(std::string message) {
    src.close();
    std::cout << message << std::endl;
    exit(1);
}


void Parser::parse() {
    typedef std::map<std::string, std::string> token;

    static bool parenCheck = false;
    static bool outCalled = false;
    bool openParen = false;
    bool closedParen = false;

    for (int i = 0; i < this -> tokens.size(); ++i) {
        for (int j = 0; j < this -> tokens[i].size(); ++j) {
            for (token::const_iterator it = this -> tokens[i][j].begin(); it != tokens[i][j].end(); ++it) {
                if (it -> second == "out") {
                    parenCheck = true;
                    outCalled = true;
                }

                if (parenCheck) {
                    if (!(openParen)) {
                        if (it -> first == "OPEN_P")  {
                            openParen = true;
                        }
                    } else {
                        if (it -> first == "OPEN_P") {
                            this -> exit_err("ERROR: Too many parenthesis on line: " + std::to_string(lineNum));
                        }
                    }
                }
            }
        }

        if (outCalled && !(openParen)) {
            this -> exit_err("ERROR: Missing parenthesis on line: " + std::to_string(lineNum));
        }

        parenCheck = false;
        outCalled = false;
        openParen = false;
    }
}
