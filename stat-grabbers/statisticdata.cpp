#include "statisticdata.h"


StatisticData::StatisticData(const map<string, string>& new_data)
{
    data = map<string, string>(new_data);
    time(&date);
}


StatisticData::~StatisticData()
{

}
