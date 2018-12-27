#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <iostream>

bool stop = false;
void finishCallBack(const std_msgs::Bool::ConstPtr& msg)
{
  stop = msg->data;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "player2");

  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("choice2", 20);
  ros::Rate loop_rate(10);

  std_msgs::String choice2;

  ros::Subscriber sub = nh.subscribe("/finish", 10, finishCallBack);

  while(ros::ok() && !stop){
    std::cout<<"Enter the player 2 choice: (rock/ paper/ scisor) ";
    std::cin>>choice2.data;
    std::cout<<"\n";

    if(choice2.data == "rock" || choice2.data == "paper" || choice2.data == "scissor"){pub.publish(choice2);}

    loop_rate.sleep();
  }

  return 0;
}
