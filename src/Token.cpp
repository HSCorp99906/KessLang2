#include "../include/Token.hpp"


std::string& Token::operator[](std::string tok) {
    return this -> tokens[tok];
}
