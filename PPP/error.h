//
// Created by Dmytrenko Kyrylo on 03.11.2025.
//

#ifndef HELLO_WORLD_ERROR_H
#define HELLO_WORLD_ERROR_H
#include <string>
#include <utility>

#include <iostream>

class Bad_exception {
public:
    Bad_exception(const std::string& message):str(message + '\n'){}

    std::string what(){ return str;}

private:
    std::string str;
};

inline void error(const std::string& msg){
    throw std::runtime_error(msg + '\n');

}


#endif //HELLO_WORLD_ERROR_H