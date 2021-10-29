#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <map>
#include <string>

typedef std::map<std::string, std::string> tokenized;


class Token {
    private:
        tokenized tokens;

    public:
        std::string& operator[](std::string tok);
};


#endif
