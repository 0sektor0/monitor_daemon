#include "diskstatisticdata.h"



DiskStatisticData::DiskStatisticData(const DiskInfo& disk) : StatisticData()
{
    name = disk.name + "_statistic";

    data["name"] = disk.name;
    data["reads"] = StringUtilities::ToString(disk.reads);
    data["writes"] = StringUtilities::ToString(disk.writes);
    data["iotime"] = StringUtilities::ToString(disk.iotime);
}


std::string DiskStatisticData::ToString()
{
    string res = name+"\n" + StringUtilities::ToString(date)+"\n";

    for(map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
        res += it->first + ": " + it->second + "\n";

    return res;
}


DiskInfo::DiskInfo(const std::string& str)
{
    vector<std::string> dinf= StringUtilities::Split(str, ' ');
    const int name_ind = 2;
    const int read_ind = 3;
    const int write_ind = 7;
    const int iotime_ind = 13;

    if(dinf.size() == 14)
    {
        name = dinf[name_ind];
        reads = StringUtilities::Stoui(dinf[read_ind]);
        writes = StringUtilities::Stoui(dinf[write_ind]);
        iotime = StringUtilities::Stoui(dinf[iotime_ind]);
    }
    else
        throw "wrong disk string format";
}


DiskInfo::DiskInfo()
{

}


DiskInfo DiskInfo::operator -(const DiskInfo& d2)
{
    DiskInfo d;
    d.name = this->name;
    d.reads = this->reads - d2.reads;
    d.writes = this->writes - d2.writes;
    d.iotime = this->iotime - d2.iotime;

    return d;
}
