#include "diskstatgrabber.h"


DiskStatGrabber::DiskStatGrabber(bool is_single) : FStatGrabber()
{
    stat_files.push_back(std::ifstream(diskinfo));

    disk_name_pattern = is_single ? "sd[a-z]$|hd[a-z]$" : "sd[a-z]\\d*$|hd[a-z]\\d*$";
    if(stat_files[0].is_open())
        for(;;)
        {
            std::string st;
            std::getline(stat_files[0], st);

            if(st != "")
            {
                DiskInfo disk(st);
                if(std::regex_match(disk.name, std::regex(disk_name_pattern)))
                    disks[disk.name] = disk;
            }
            else
            {
                stat_files[0].clear();
                stat_files[0].seekg(0);
                break;
            }
        }
    else
    {
        string message = "DISK statistic grabber constructor cant open " + diskinfo;
        syslog(LOG_ERR, message.c_str());
        exit(1);
    }
}


void DiskStatGrabber::Grab()
{
    //чтение данных о дисках
    if(stat_files[0].is_open())
        for(;;)
        {
            std::string st;
            std::getline(stat_files[0], st);

            if(st != "")
            {
                DiskInfo disk(st);

                if(std::regex_match(disk.name, std::regex(disk_name_pattern)))
                {
                    if(!disks.count(disk.name))
                        disks[disk.name] = disk;

                    stat_data.push_back(shared_ptr<DiskStatisticData>(new DiskStatisticData(disk - disks[disk.name])));
                    disks[disk.name] = disk;
                }
            }
            else
                break;
        }
    else
    {
        string message = "DISK statistic grabber cant open " + diskinfo;
        syslog(LOG_ERR, message.c_str());
        throw std::runtime_error(message);
        //exit(1);
    }

    stat_files[0].clear();
    stat_files[0].seekg(0);
}
