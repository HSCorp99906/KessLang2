#ifndef KEYS_HPP
#define KEYS_HPP

#include <string>
#include <map>


class Key {
    private:
        std::map<std::string, char*> keys;

    public:
        void operator<<(std::string key);

        bool count(std::string key);

        std::string operator[](std::string key);
};


#endif
