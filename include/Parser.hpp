#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

typedef std::vector<std::vector<std::map<std::string, std::string>>> __tokens;
typedef std::map<std::string, std::string> token;
extern std::ifstream src;


class Parser {
    private:
        __tokens tokens;
        std::vector<token> tree;
        token varsCopy;
        void exit_err(std::string message);

    public:
        Parser(__tokens tokens);

        std::vector<std::map<std::string, std::string>> parse();
};


#endif
