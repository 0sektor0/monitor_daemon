# !bin/bash
cd build_daemon  			 		
cmake .
make  			 		 	
cd -					 	
cp build_daemon/monitor_daemon /usr/bin/ 
systemctl daemon-reload 	 	 

mkdir /var/log/monitor_daemon 				
cp monitor_daemon.service /etc/systemd/system/  
systemctl start monitor_daemon 


cd build_utility 
cmake .
make 
cd - 
cp build_utility/mdu /usr/bin 

echo 'monitor_daemon installed'

