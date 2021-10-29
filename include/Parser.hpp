#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>


typedef std::vector<std::vector<std::map<std::string, std::string>>> __tokens;
extern std::ifstream src;
extern unsigned int lineNum;

class Parser {
    private:
        __tokens tokens;

        void exit_err(std::string message);

    public:
        Parser(__tokens tokens);

        void parse();
};


#endif
