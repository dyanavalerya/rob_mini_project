#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <iostream>

bool stop = false;
void finishCallBack(const std_msgs::Bool::ConstPtr& msg)
{
  ROS_INFO("l-a luat");
  stop = msg->data;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "player1");

  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("choice1", 20);
  ros::Rate loop_rate(10);

  std_msgs::String choice1;

  ros::Subscriber sub = nh.subscribe("/finish", 10, finishCallBack);

  while(ros::ok() && !stop){
    std::cout<<"Enter the player 1 choice: (rock/ paper/ scisor) ";
    std::cin>>choice1.data;
    std::cout<<"\n";

    if(choice1.data == "rock" || choice1.data == "paper" || choice1.data == "scissor"){pub.publish(choice1);}
    loop_rate.sleep();
  }

  return 0;
}
