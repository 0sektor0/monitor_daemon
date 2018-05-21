# !bin/bash
systemctl stop monitor_daemon &&

rm build_daemon/monitor_daemon
rm /usr/bin/monitor_daemon 
rm -rf /var/log/monitor_daemon 
rm /etc/systemd/system/monitor_daemon.service 

rm /usr/bin/mdu
rm build_utility/mdu

systemctl daemon-reload
echo 'monitor_daemon deleted'

