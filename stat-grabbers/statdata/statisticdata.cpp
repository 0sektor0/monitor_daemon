#include "statisticdata.h"


StatisticData::StatisticData(map<std::string, std::string>& new_data)
{
    data = move(new_data);
    time(&date);
}


bool StatisticData::operator<(const StatisticData& rhs)
{
    return date < rhs.date;
}


StatisticData::StatisticData()
{
    time(&date);
}
