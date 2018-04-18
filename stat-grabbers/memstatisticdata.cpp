#include "memstatisticdata.h"



MemStatisticData::MemStatisticData(map<std::string, std::string>& new_data) : StatisticData(new_data)
{
    name="meminfo";
}


std::string MemStatisticData::ToString()
{
    std::string res = "";

    for(auto& item : data)
        res = "";//std::string(item.first + ": " + item.second + " KB\n");

    return "";
}
