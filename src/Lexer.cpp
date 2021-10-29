#include "../include/Lexer.hpp"


Lexer::Lexer(std::string src) {
    this -> src = src;
}


std::vector<std::map<std::string, std::string>> Lexer::tokenize() {
    typedef std::map<std::string, std::string> tok;
    tok curToken;

    std::vector<tok> tokens;
    boost::split(this -> split_src, this -> src, boost::is_any_of(" "));

    for (int i = 0; i < this -> split_src.size(); ++i) {
        std::smatch m;
        std::regex_search(this -> split_src[i], m, std::regex("out"));

        for (int j = 0; j < m.size(); ++j) {
            if (m[i] == "out") {
                curToken["IDENTIFIER"] = m[i];

                for (int e = 0; e < this -> split_src[i].size(); ++e) {
                    if (this -> split_src[i][e] == OPEN_PAREN) {
                        curToken["OPEN_P"] = this -> split_src[i][e];
                        tokens.push_back(curToken);
                        curToken.clear();
                    } else if (this -> split_src[i][e] == CLOSED_PAREN) {
                        curToken["CLOSED_P"] = this -> split_src[i][e];
                        tokens.push_back(curToken);
                        curToken.clear();
                    } else if (this -> split_src[i][e] == QUOTE || this -> split_src[i][e] == SINGLE_QUOTE) {
                        curToken["QUOTE"] = this -> split_src[i][e];
                        tokens.push_back(curToken);
                        curToken.clear();
                    } else if (this -> split_src[i][e] == END_STATEMENT) {
                        curToken["STATEMENT_END"] = this -> split_src[i][e];
                        tokens.push_back(curToken);
                        curToken.clear();
                    }
                }
            }
        }

        for (int j = 0; j < this -> split_src[i].size(); ++j) {
            switch (split_src[i][j]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    curToken["INTEGER"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
             }
        }
    }

    return tokens;
}
