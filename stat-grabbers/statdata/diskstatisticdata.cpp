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

    //индексы значений определены в соответсвие с общей структурой файла дисков
    if(dinf.size() == INFO_COUNT)
    {
        name = dinf[NAME_INDEX];
        reads = StringUtilities::Stoui(dinf[READS_INDEX]);
        writes = StringUtilities::Stoui(dinf[WRITES_INDEX]);
        iotime = StringUtilities::Stoui(dinf[IOTIME_INDEX]);
    }
    else
    {
        std::string message = "Wrong disk string format: " + str;
        syslog(LOG_ERR, message.c_str());
        throw std::runtime_error(message);
        //exit(1);
    }
}


DiskInfo::DiskInfo()
{
    name = DEFAULT_DISK_NAME;
    reads = 0;
    writes = 0;
    iotime = 0;
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
