#include "memstatisticdata.h"



MemStatisticData::MemStatisticData(map<std::string, std::string>& new_data) : StatisticData(new_data)
{
    name="memory_statistic";
}


std::string MemStatisticData::ToString()
{
    string res = name+"\n" + StringUtilities::ToString(date)+"\n";

    for(map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
        res += it->first + ": " + it->second + " KB\n";

    return res;
}
