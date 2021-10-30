#ifndef LEXER_HPP
#define LEXER_HPP

#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <map>
#include <iostream>

#define OPEN_PAREN '('
#define CLOSED_PAREN ')'
#define QUOTE '"'
#define SINGLE_QUOTE '\''
#define END_STATEMENT ';'
#define TAB '\t'
#define WHITESPACE ' '
#define NEWLINE '\n'


class Lexer {
    private:
        std::string src;
        std::vector<std::string> split_src;

    public:
        Lexer(std::string src);

        std::vector<std::map<std::string, std::string>> tokenize();
};


#endif
