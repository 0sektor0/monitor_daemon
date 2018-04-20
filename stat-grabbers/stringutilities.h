#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H
#define _GLIBCXX_USE_CXX11_ABI 0

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


class StringUtilities
{
public:
    static unsigned int Stoui(const std::string&);
    static std::vector<std::string> Split(const std::string&, char);
    template<typename T>
        static std::string ToString(const T&);


private:
    StringUtilities();
};

#endif // STRINGUTILITIES_H
