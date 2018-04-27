#include "stringutilities.h"

using namespace StringUtilities;


std::vector<std::string> StringUtilities::Split(const std::string& str_to_split, char delimeter)
{
    std::vector<std::string> splitted_strings;
    std::stringstream ss(str_to_split);
    std::string item;

    while (std::getline(ss, item, delimeter))
       if(item != "")
           splitted_strings.push_back(item);

    return splitted_strings;
}


unsigned int StringUtilities::Stoui(const std::string& s)
{
    unsigned long lresult = stoul(s, 0, 10);
    unsigned int result = lresult;

    if (result != lresult)
        throw std::out_of_range("size mismatch");

    return result;
}

