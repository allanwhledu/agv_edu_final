#!/bin/bash -e
sleep 2
roslaunch  agv_tcp_velocity laser.launch&
sleep 1
roslaunch ira_laser_tools laserscan_multi_merger.launch&
sleep 1
# rosrun map_server map_server src/map.yaml&
sleep 1
# roslaunch laser_scan_matcher demo.launch&
sleep 1
# roslaunch amcl amcl_omni.launch&
roslaunch my_laser_matcher my_localize.launch&
sleep 1
roslaunch agv_tcp_velocity move_base.launch&
sleep 5
sudo chmod 777 /dev/ttyUSB0
sleep 2
rosrun soccer_maxon soccer_maxon_node&
sleep 1

source devel/setup.bash&
#source /home/agv/dynamic_avoid_person/devel/setup.bash&
#roslaunch kinova_bringup kinova_robot.launch&
#sleep 3
#rosrun openni2_tracker openni2_tracker&
#sleep 5
#rosrun avoid_person_node avoid_person_node&
#sleep 1
#source /home/agv/agv_ws/devel/setup.bash&
roslaunch move_forward move_and_avoid_dynamic_object.launch&
