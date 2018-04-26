#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


namespace StringUtilities
{
    unsigned int Stoui(const std::string&);
    std::vector<std::string> Split(const std::string&, char);

    template<typename T>
        std::string ToString(const T& t)
        {
            std::stringstream ss;
            ss << t;

            return ss.str();
        }
}

#endif // STRINGUTILITIES_H
