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
            }
        }

        for (int j = 0; j < this -> split_src[i].size(); ++j) {
            switch (this -> split_src[i][j]) {
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
                    break;
            }

            switch (this -> split_src[i][j]) {
                case '(':
                    curToken["OPEN_P"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
                case ')':
                    curToken["CLOSED_P"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
                case '"':
                    curToken["QUOTE"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
            }

            if (this -> split_src[i][j] == ';') {
                curToken["STATEMENT_END"] = this -> split_src[i][j];
                tokens.push_back(curToken);
                curToken.clear();
            }

            switch (this -> split_src[i][j]) {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                    curToken["LETTER"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;

            }

            switch (split_src[i][j]) {
                case '`':
                    curToken["SPACE"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
                case ',':
                    curToken["PUNCTUATION"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
                case '!':
                    curToken["PUNCTUATION"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
                case '.':
                    curToken["PUNCTUATION"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;
                case '?':
                    curToken["PUNCTUATION"] = this -> split_src[i][j];
                    tokens.push_back(curToken);
                    curToken.clear();
                    break;

            }
        }
    }

    return tokens;
}
