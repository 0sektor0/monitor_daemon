#include "diskstatgrabber.h"


DiskStatGrabber::DiskStatGrabber() : FStatGrabber()
{
    stat_files.push_back(std::ifstream(diskinfo));

    if(stat_files[0].is_open())
        for(;;)
        {
            std::string st;
            std::getline(stat_files[0], st);

            if(st != "")
            {
                Disk d(st);
                disks[d.name] = d;
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
                Disk disk(st);

                if(!disks.count(disk.name))
                    disks[disk.name] = disk;

                stat_data.push_back(new DiskStatisticData(disk - disks[disk.name]));
                disks[disk.name] = disk;
            }
            else
                break;
        }
    else
        throw "Cannot open disk file";

    stat_files[0].clear();
    stat_files[0].seekg(0);
}
