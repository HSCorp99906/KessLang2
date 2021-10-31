#include "../include/Keys.hpp"


void Key::operator<<(std::string key) {
    this -> keys[key] = NULL;
}


bool Key::count(std::string key) {
    return this -> keys.count(key);
}


std::string Key::operator[](std::string key) {
    if (!(this -> keys.count(key))) {
        return "error";
    } else {
        return key;
    }
}
