#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
#include <string>

[[noreturn]]
inline void error(std::string msg){
    std::cout << msg << std::endl;
    throw(1);
}

#endif // ERRORHANDLING_H
