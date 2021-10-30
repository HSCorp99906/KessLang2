#include "../include/Lexer.hpp"
#include "../include/Parser.hpp"
#include "../include/ExecutionHandler.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <regex>


std::ifstream src;

int main() {
    typedef std::map<std::string, std::string> tok;
    typedef std::vector<std::vector<std::map<std::string, std::string>>> __tokens;

    src.open("kesslang.kess");
    std::string line;

    __tokens _tokens;

    while (std::getline(src, line)) {

        if (line == "") {
            Lexer lex(";");
            continue;
        }

        line = std::regex_replace(line, std::regex("\\s"), "`");

        Lexer lex(line);
        std::vector<tok> tokens = lex.tokenize();

        for (int i = 0; i < tokens.size(); ++i) {
            for (tok::const_iterator it = tokens[i].begin(); it != tokens[i].end(); ++it) {
                std::cout << "[" << it -> first << ": " << it -> second << "]" << std::endl;

            }
        }

        _tokens.push_back(tokens);

        std::cout << "\n" << std::endl;
    }

    Parser parser(_tokens);
    std::vector<tok> parsetree = parser.parse();

    for (int i = 0; i < parsetree.size(); ++i) {
        execute(parsetree[i]);
    }
}
