#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <signal.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
#include <string.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <cmath>
#include <std_msgs/Int32.h>
#include "move_forward/agv_call.h"


int main(int argc, char** argv)
{

    ros::init(argc, argv, "get_state_car");
    ros::NodeHandle node;

    // pub
    ros::Publisher agv_state_pub = node.advertise<std_msgs::Int32>("/agv_state", 100);

    // server
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base",true);


//    ros::spinOnce();
    std_msgs::Int32 agv_state_msg;
    agv_state_msg.data=0;

    ROS_INFO("Checking move_base server...");
    while(!ac.waitForServer(ros::Duration(1)))
    {
        ROS_INFO("Can't connected to move base server");
        agv_state_msg.data = 0;
        agv_state_pub.publish(agv_state_msg);
    }

    ROS_INFO("Move_base server connected.");
    ROS_INFO_STREAM("Waiting for new goal.");

    agv_state_msg.data = 1;
    agv_state_pub.publish(agv_state_msg);

    ros::Duration two_seconds(2.0);
    two_seconds.sleep();

    agv_state_msg.data = 2;
    agv_state_pub.publish(agv_state_msg);

    ros::Rate loop_rate(5);
    while (ros::ok()){
        agv_state_msg.data = 2;
        agv_state_pub.publish(agv_state_msg);
        loop_rate.sleep();
    }

//    // 主循环
//    ros::Rate loop_rate(5);
//    while (ros::ok()){
//
//        ros::spinOnce();
//        //Allow 1 minute to get there
//        bool finished_within_time = ac.waitForResult(ros::Duration(1));
//
//        if(ac.getState() == actionlib::SimpleClientGoalState::ACTIVE)
//        {
//            agv_state_msg.data = 1;
//            ROS_INFO_STREAM("Waiting for new goal.");
//        }
//
//        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//        {
//            agv_state_msg.data = 2;
//            ROS_INFO_STREAM("Still getting to goal.");
//        }
//
//        agv_state_pub.publish(agv_state_msg);
//
//        loop_rate.sleep();
//    }
    return 0;
}