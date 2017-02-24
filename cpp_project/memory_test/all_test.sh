#!/bin/bash   
#rm -rf ltt console nohup.out

kill_process(){
    ps xf|grep ltt|awk '{print $1}'|xargs kill -9
	rm -rf ~/esogxig/ltt.log
}

choose_ue_num(){
    echo -e "input ue num:" 
    read  ue_num 
    case $ue_num in
		500)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_500  console/config/mobile.conf
		;;
		1k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_1k  console/config/mobile.conf
		;;
		2k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_2k  console/config/mobile.conf
		;;
		3k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_3k  console/config/mobile.conf
		;;
		4k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_4k  console/config/mobile.conf
		;;
		5k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_5k  console/config/mobile.conf
		;;
		6k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_6k  console/config/mobile.conf
		;;
		7k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_7k  console/config/mobile.conf
		;;
		8k)  echo "input UE num $ue_num"
		yes |cp bak_config/mobile.conf_dummy_8k  console/config/mobile.conf
		;;
		*)  echo "input is not in 500--8k, input is $ue_num"
		;;
    esac
}

copy_config(){
    yes |cp bak_config/infra.yaml  console/config/
    yes |cp bak_config/vlan_config.sh  console/vlan_config.sh 
}

choose_ltt_core_for_620(){
    echo -e "input core num:" 
    read  core_num 
    case $core_num in
		1)  echo 'set ltt core 1'
		nohup ./ltt -c 0x5 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2)" >ltt.log 2>&1 &
		;;
		
		2)  echo 'set ltt core 2'
		nohup ./ltt -c 0x15 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4)" >ltt.log 2>&1 &
		;;
		
		3)  echo 'set ltt core 3'
		nohup ./ltt -c 0x55 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid  --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6)" >ltt.log 2>&1 &
		;;
		
		4)  echo 'set ltt core 4'
		nohup ./ltt -c 0x155 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8)" >ltt.log 2>&1 &
		;;
		
		5)  echo 'set ltt core 5'
        nohup ./ltt -c 0x555 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10)" >ltt.log 2>&1 &
		;;
		
		6)  echo 'set ltt core 6'
		nohup ./ltt -c 0x1555 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12)" >ltt.log 2>&1 &
		;;
		
		7)  echo 'set ltt core 7'
		nohup ./ltt -c 0x5555 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14)" >ltt.log 2>&1 &
		;;
		
		8)  echo 'set ltt core 8'
		nohup ./ltt -c 0x5557 -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1)" >ltt.log 2>&1 &
		;;
		
		9)  echo 'set ltt core 9'
		nohup ./ltt -c 0x555f -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3)" >ltt.log 2>&1 & 
		;;
		
		10)  echo 'set ltt core 10'
		nohup ./ltt -c 0x557f -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3),(0,9,5),(1,9,5)" >ltt.log 2>&1 &
		;;
		
		11)  echo 'set ltt core 11'
		nohup ./ltt -c 0x55ff -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3),(0,9,5),(1,9,5),(0,10,7),(1,10,7)" >ltt.log 2>&1 &
		;;
		
		12)  echo 'set ltt core 12'
		nohup ./ltt -c 0x57ff -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3),(0,9,5),(1,9,5),(0,10,7),(1,10,7),(0,11,9),(1,11,9)" >ltt.log 2>&1 &
		;;
		
		13)  echo 'set ltt core 13'
		nohup ./ltt -c 0x5fff -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3),(0,9,5),(1,9,5),(0,10,7),(1,10,7),(0,11,9),(1,11,9),(0,12,11),(1,12,11)" >ltt.log 2>&1 &
		;;
		
		14)  echo 'set ltt core 14'
		nohup ./ltt -c 0x7fff -n 4 -- -p 0x3  -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3),(0,9,5),(1,9,5),(0,10,7),(1,10,7),(0,11,9),(1,11,9),(0,12,11),(1,12,11),(0,13,13),(1,13,13)" >ltt.log 2>&1 &
		;;
		
		15)  echo 'set ltt core 15'
		nohup ./ltt -c 0xffff -n 4 -- -p 0x3 -i 1 --pid-file /var/run/ltt.pid --config="(0,0,2),(1,0,2),(0,1,4),(1,1,4),(0,2,6),(1,2,6),(0,3,8),(1,3,8),(0,4,10),(1,4,10),(0,5,12),(1,5,12),(0,6,14),(1,6,14),(0,7,1),(1,7,1),(0,8,3),(1,8,3),(0,9,5),(1,9,5),(0,10,7),(1,10,7),(0,11,9),(1,11,9),(0,12,11),(1,12,11),(0,13,13),(1,13,13),(0,14,15),(1,14,15)" >ltt.log 2>&1 &
		;;
		
		*)  echo "input is not in 1--15, input is $core_num"
		;;
    esac       
    echo "ltt process is running"
    return $core_num 
}

config_vlan(){
    echo -e "config vlan:" 
    read  confirm 
    if [ $confirm == 'yes' ];
	then 
        source ~/esogxig/console/vlan_config.sh 519 4
		if [ $? -eq 0 ];
		then 
		    echo "config vlan correct"	
		else
		    echo "config vlan error"
        fi			
	else
        echo "config vlan error, input is $confirm"	
    fi
}

config_vlan_auto(){
    echo -e "auto config vlan " 
	sleep 10
	a=1
    until [ $a -eq 0 ]
    do
       grep -rin "Enabling CRC32 instruction for custom_filter_ft_ipv6 hashing" ~/esogxig/ltt.log >/dev/null
       a=$?
	   sleep 3
    done
    
	split=`echo $HOSTNAME |cut -d "." -f1`
	
    case $split in
		cnshdallas01|cnshdallas01)  
		    echo "set vlan in $split"
		    source ~/esogxig/console/vlan_config.sh 519 4
		;;
		
		selnpctool-012-07-01|selnpctool-012-07-02)  
		    echo "set vlan in $split"
		    source ~/esogxig/console/vlan_config.sh 402 4
		;;
		
		selnpctool-012-08-01|selnpctool-012-08-02)  
		    echo "set vlan in $split"
		    source ~/esogxig/console/vlan_config.sh 451 4
		;;
		
		*)  
		    echo "hostname error $split"
		;;
    esac  
    
    if [ $? -eq 0 ];
    then 
        echo "config vlan correct"	
    else
        echo "config vlan error"
    fi			

}

add_ue(){
    python3 ~/esogxig/console/cli.py --infra infra.yaml --ip ipv4 ltt --mobile mobile.conf --rampup 20  
	echo " ltt is ok"
}

job_tracker(){
    python3 ~/esogxig/console/cli.py ltt --job_tracker 
}

exit_program(){
    echo -e "exit program ?" 
    read  ext 
    if [ $ext == "yes" ];
	then
#	    kill_process
	    exit
    fi	
}

while true
do
    echo "config environment"
    cd ~/esogxig
    kill_process
    copy_config
    choose_ue_num
    echo "begin running ltt"
    choose_ltt_core_for_620
    config_vlan_auto
    add_ue
	echo "ltt case running: core NO: $core_num , UE NO: $ue_num"
    exit_program
done

 


