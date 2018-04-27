#include "statisticdata.h"


StatisticData::StatisticData(map<std::string, std::string>& new_data)
{
    data = move(new_data);
    time(&date);
}


StatisticData::StatisticData()
{
    time(&date);
}


const time_t& StatisticData::GetDate()
{
    return date;
}


const std::string& StatisticData::GetName()
{
    return name;
}
