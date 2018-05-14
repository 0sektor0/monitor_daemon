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
        throw "Cannot open disk file";
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

                    stat_data.push_back(new DiskStatisticData(disk - disks[disk.name]));
                    disks[disk.name] = disk;
                }
            }
            else
                break;
        }
    else
        throw "Cannot open disk file";

    stat_files[0].clear();
    stat_files[0].seekg(0);
}
