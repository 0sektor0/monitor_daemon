#include "cpustatgrabber.h"


CpuStatGrabber::CpuStatGrabber(bool is_single) : FStatGrabber()
{
    stat_files.push_back(std::ifstream(cpuinfo));

    cpu_count = 0;
    cpu_name_pattern = is_single ? "cpu$" : "cpu\\d*$";

    if(stat_files[0].is_open())
    {
        bool is_cpu = true;
        std::string st;

        while(is_cpu)
        {
            std::getline(stat_files[0], st);
            is_cpu = CpuInfo::IsCpuFormat(st, cpu_name_pattern);
            if(is_cpu)
            {
                CpuInfo cpu(st, cpu_name_pattern);
                cpus[cpu.name] = cpu;
                cpu_count++;
            }
        }
    }
    else
    {
        string message = "CPU statistic grabber constructor cant open " + cpuinfo;
        syslog(LOG_ERR, message.c_str());
        exit(1);
    }

    stat_files[0].clear();
    stat_files[0].seekg(0);
}


void CpuStatGrabber::Grab()
{
    if(stat_files[0].is_open())
    {
        std::string st;

        for(int i = 0; i < cpu_count; i++)
        {
            std::getline(stat_files[0], st);
            CpuInfo cpu(st, cpu_name_pattern);

            if(!cpus.count(cpu.name))
                cpus[cpu.name] = cpu;

            stat_data.push_back(shared_ptr<CpuStatisticData>(new CpuStatisticData(cpu - cpus[cpu.name])));
            cpus[cpu.name] = cpu;
        }
    }
    else
    {
        string message = "CPU statistic grabber cant open " + cpuinfo;
        syslog(LOG_ERR, message.c_str());
        throw std::runtime_error(message);
        //exit(1);
    }

    stat_files[0].clear();
    stat_files[0].seekg(0);
}






























