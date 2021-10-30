#include "../include/Lexer.hpp"
#include "../include/Parser.hpp"
#include "../include/ExecutionHandler.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <regex>

#define KESS_DEBUG

std::ifstream src;


int main(int argc, char* argv[]) {
    typedef std::map<std::string, std::string> tok;
    typedef std::vector<std::vector<std::map<std::string, std::string>>> __tokens;

    src.open(argv[1]);
    std::string line;

    if (!(src)) {
        std::cout << "ERROR: File does not exist (terminated)." << std::endl;
        src.close();
        exit(1);
    }

    __tokens _tokens;

    while (std::getline(src, line)) {

        if (line == "") {
            line = ";";
        }

        line = std::regex_replace(line, std::regex("\\s"), "`");

        Lexer lex(line);
        std::vector<tok> tokens = lex.tokenize();

        #ifdef KESS_DEBUG  /* Dumps Tokens */
        for (int i = 0; i < tokens.size(); ++i) {
            for (tok::const_iterator it = tokens[i].begin(); it != tokens[i].end(); ++it) {
                std::cout << "[" << it -> first << ": " << it -> second << "]" << std::endl;

            }
        }
        #endif

        _tokens.push_back(tokens);

        #ifdef KESS_DEBUG
        std::cout << "\n" << std::endl;
        #endif
    }

    Parser parser(_tokens);
    std::vector<tok> parsetree = parser.parse();

    for (int i = 0; i < parsetree.size(); ++i) {
        execute(parsetree[i]);
    }
}
