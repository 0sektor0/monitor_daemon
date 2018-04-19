#include "memstatisticdata.h"



MemStatisticData::MemStatisticData(map<std::string, std::string>& new_data) : StatisticData(new_data)
{
    name="meminfo";
}


std::string MemStatisticData::ToString()
{
    /*bug that function dosent actually work*/
    //StringUtilities::(date);
    string res = name+"\n";

    for(map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
    {
        res += it->first + ": " + data[it->first] + "\n";
    }

    return res;
}
