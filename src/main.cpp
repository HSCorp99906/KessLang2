#include "../include/Lexer.hpp"
#include "../include/Parser.hpp"
#include <vector>
#include <fstream>
#include <string>


std::ifstream src;
unsigned int lineNum = 0;

int main() {
    typedef std::map<std::string, std::string> tok;
    typedef std::vector<std::vector<std::map<std::string, std::string>>> __tokens;

    src.open("kesslang.kess");
    std::string line;

    __tokens _tokens;

    while (std::getline(src, line)) {
        ++lineNum;
        Lexer lex(line);
        std::vector<tok> tokens = lex.tokenize();

        for (int i = 0; i < tokens.size(); ++i) {
            for (tok::const_iterator it = tokens[i].begin(); it != tokens[i].end(); ++it) {
                std::cout << "[" << it -> first << ": " << it -> second << "]" << std::endl;

            }
        }

        _tokens.push_back(tokens);

        std::cout << "\n" << std::endl;

        Parser parser(_tokens);
        parser.parse();
    }
}
