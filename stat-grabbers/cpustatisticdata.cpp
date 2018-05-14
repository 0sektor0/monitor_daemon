#include "cpustatisticdata.h"


CpuStatisticData::CpuStatisticData(const CpuInfo& cpu)
{
    name = cpu.name + "_statistic";

    data["name"] = cpu.name;
    data["user"] = StringUtilities::ToString(cpu.user);
    data["nice"] = StringUtilities::ToString(cpu.nice);
    data["system"] = StringUtilities::ToString(cpu.system);
    data["idle"] = StringUtilities::ToString(cpu.idle);
    data["iowait"] = StringUtilities::ToString(cpu.iowait);
    data["irq"] = StringUtilities::ToString(cpu.irq);
    data["softirq"] = StringUtilities::ToString(cpu.softirq);

    double sum = (double)(cpu.user + cpu.nice + cpu.system + cpu.idle + cpu.iowait + cpu.irq + cpu.softirq);
    data["user_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.user, sum));
    data["nice_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.nice, sum));
    data["system_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.system, sum));
    data["idle_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.idle, sum));
    data["iowait_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.iowait, sum));
    data["irq_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.irq, sum));
    data["softirq_per"] = StringUtilities::ToString(CalcPercentage((double) cpu.softirq, sum));
}


double CpuStatisticData::CalcPercentage(const double& val, const double& sum)
{
    return val/sum;
}


std::string CpuStatisticData::ToString()
{
    string res = name+"\n" + StringUtilities::ToString(date)+"\n";

    for(map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
        res += it->first + ": " + it->second + "\n";

    return res;
}


CpuInfo::CpuInfo(const std::string& str, const std::string& pattern)
{
    vector<std::string> vals = StringUtilities::Split(str, ' ');
    if(!CpuInfo::IsCpuFormat(vals, pattern))
        throw "wrong cpu string format";

    name = vals[0];
    user = StringUtilities::Stoui(vals[1]);
    nice = StringUtilities::Stoui(vals[2]);
    system = StringUtilities::Stoui(vals[3]);
    idle = StringUtilities::Stoui(vals[4]);
    iowait = StringUtilities::Stoui(vals[5]);
    irq = StringUtilities::Stoui(vals[6]);
    softirq = StringUtilities::Stoui(vals[7]);
}


bool CpuInfo::IsCpuFormat(const vector<std::string>& vals, const std::string& pattern)
{
    if(vals.size() != 11) return false;
    return std::regex_match(vals[0], std::regex(pattern));
}


bool CpuInfo::IsCpuFormat(const std::string& str, const std::string& pattern)
{
    vector<std::string> vals = StringUtilities::Split(str, ' ');
    return CpuInfo::IsCpuFormat(vals, pattern);
}


CpuInfo CpuInfo::operator -(const CpuInfo& c)
{
    CpuInfo cu;
    cu.name = this->name;
    cu.user = this->user - c.user;
    cu.nice = this->nice - c.nice;
    cu.system = this->system - c.system;
    cu.idle = this->idle - c.idle;
    cu.iowait = this->iowait - c.iowait;
    cu.irq = this->irq - c.irq;
    cu.softirq = this->softirq - c.softirq;

    return cu;
}
