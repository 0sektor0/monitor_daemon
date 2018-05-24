#include "netdevgrabbers.h"



NetDevGrabber::NetDevGrabber(const bool& is_raw)
{
    this->is_raw = is_raw;
    stat_files.push_back(std::ifstream(netdevinfo));

    if(stat_files[0].is_open())
    {
        if(!is_raw)
        {
            std::string st;
            //первые 2 строки файла не содержат важной информации
            std::getline(stat_files[0], st);
            std::getline(stat_files[0], st);
            std::getline(stat_files[0], st);

            while(st != "")
            {
                NetDevInfo ndinfo(st);
                interfaces[ndinfo.interface] = ndinfo;
                std::getline(stat_files[0], st);
            }
        }

        stat_files[0].clear();
        stat_files[0].seekg(0);
    }
    else
    {
        std::string message = "NETDEV statistic grabber constructior cant open" + netdevinfo;
        syslog(LOG_ERR, message.c_str());
        exit(1);
    }
}


void NetDevGrabber::Grab()
{
    if(is_raw)
        GrabRaw();
    else
        GrabDiffer();
}


void NetDevGrabber::GrabRaw()
{
    //чтение данных о дисках
    if(stat_files[0].is_open())
    {
        std::string st;
        //первые 2 строки файла не содержат важной информации
        std::getline(stat_files[0], st);
        std::getline(stat_files[0], st);
        std::getline(stat_files[0], st);

        while(st != "")
        {
            NetDevInfo interface(st);
            stat_data.push_back(shared_ptr<NetDevStatisticData>(new NetDevStatisticData(interface)));
            std::getline(stat_files[0], st);
        }
    }
    else
    {
        string message = "interface statistic grabber cant open " + netdevinfo;
        syslog(LOG_ERR, message.c_str());
        throw std::runtime_error(message);
    }

    stat_files[0].clear();
    stat_files[0].seekg(0);
}


void NetDevGrabber::GrabDiffer()
{
    //чтение данных о дисках
    if(stat_files[0].is_open())
    {
        std::string st;
        //первые 2 строки файла не содержат важной информации
        std::getline(stat_files[0], st);
        std::getline(stat_files[0], st);
        std::getline(stat_files[0], st);

        while(st != "")
        {
            NetDevInfo interface(st);

            if(!interfaces.count(interface.interface))
                interfaces[interface.interface] = interface;

            stat_data.push_back(shared_ptr<NetDevStatisticData>(new NetDevStatisticData(interface - interfaces[interface.interface])));
            interfaces[interface.interface] = interface;

            std::getline(stat_files[0], st);
        }
    }
    else
    {
        string message = "interface statistic grabber cant open " + netdevinfo;
        syslog(LOG_ERR, message.c_str());
        throw std::runtime_error(message);
    }

    stat_files[0].clear();
    stat_files[0].seekg(0);
}
