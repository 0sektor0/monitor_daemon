#include "statgrabber.h"
#include <memory>


StatGrabber::StatGrabber()
{
    stat_data = vector<shared_ptr<StatisticData>>();
}


vector<shared_ptr<StatisticData>> StatGrabber::MoveStatistic()
{
    if (stat_data.empty())
        throw std::runtime_error("stat-grabber is empty");

    vector<shared_ptr<StatisticData>> dest;
    dest = move(stat_data);
    return dest;
}


bool StatGrabber::IsEmpty()
{
    return stat_data.empty();
}


int StatGrabber::GetStatisticNum()
{
    return stat_data.size();
}


StatGrabber::~StatGrabber()
{
}
