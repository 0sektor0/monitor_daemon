#include "diskstatgrabber.h"


DiskStatGrabber::DiskStatGrabber() : StatGrabber()
{
    stat_files.push_back(ifstream(diskinfo));

    if(stat_files[0].is_open())
        for(;;)
        {
            std::string st;
            std::getline(stat_files[0], st);

            if(st != "")
                disks.push_back(Disk(st));
            else
                break;
        }
    else
        throw "Cannot open disk file";

    stat_files[0].seekg(0);
}


void DiskStatGrabber::Parse()
{

}


Disk::Disk(const std::string& str)
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
