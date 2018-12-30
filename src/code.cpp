#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Int16.h>
#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include <string.h>
#include <iostream>

std::string choice1 = "choice1";
std::string choice2 = "choice2";
int player1points = 0, player2points = 0;
bool stop = false;
std_msgs::Bool stop2;

// Prototype functions
void gameCallback1(const std_msgs::String::ConstPtr& msg);
void gameCallback2(const std_msgs::String::ConstPtr& msg);
void compare(ros::Publisher publisher);
void goForward();
void goBackward();

int main(int argc, char **argv){

  ros::init(argc, argv, "core");
  ros::NodeHandle nh;
  ros::Subscriber sub1 = nh.subscribe("choice1", 20, gameCallback1);
  ros::Subscriber sub2 = nh.subscribe("choice2", 20, gameCallback2);
  ros::Publisher finish = nh.advertise<std_msgs::Bool>("/finish", 10);

  ros::Duration(1.0).sleep();

  while(ros::ok() && !stop){
    if(choice1 != "choice1" && choice2 != "choice2"){
      compare(finish);
      choice1 = "choice1";
      choice2 = "choice2";
      stop2.data = stop;
      finish.publish(stop2);
    }
    ros::spinOnce();
  }


  return 0;
}

void gameCallback1(const std_msgs::String::ConstPtr& msg)
{
  choice1 = msg->data;
}

void gameCallback2(const std_msgs::String::ConstPtr& msg)
{
  choice2 = msg->data;
}

void goForward(){
  ros::NodeHandle n;
  ros::Publisher cmd_vel_pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  geometry_msgs::Twist go;
  ros::Time start = ros::Time::now();

  go.linear.x = 0.5;
  go.angular.z = 0.0;

  while (ros::ok() && ros::Time::now() - start < ros::Duration(2.0)) {
    cmd_vel_pub1.publish(go);
    ros::Duration(0.2).sleep();
  }

}

void goBackward(){
  ros::NodeHandle n;
  ros::Publisher cmd_vel_pub2 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  geometry_msgs::Twist go;
  ros::Time start = ros::Time::now();
  go.linear.x = -0.5;
  go.angular.z = 0.0;

  while (ros::ok() && ros::Time::now() - start < ros::Duration(2.0)) {
    cmd_vel_pub2.publish(go);
    ros::Duration(0.2).sleep();
  }

}

void winSpin(){
  ros::NodeHandle n;
  ros::Publisher cmd_vel_pub3 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  geometry_msgs::Twist go;
  ros::Time start = ros::Time::now();
  go.linear.x = 0.0;
  go.angular.z = 2.25;

  while (ros::ok() && ros::Time::now() - start < ros::Duration(10.0)) {
    cmd_vel_pub3.publish(go);
    ros::Duration(0.2).sleep();
  }

}

void compare(ros::Publisher publisher){

    if(choice1 == "rock" && choice2 == "scissor") {
      ROS_INFO("1p goes to Player 1!");
      player1points++;
      player2points--;
      goForward();
    }else
    if(choice1 == "scissor" && choice2 == "rock"){
      ROS_INFO("1p goes to Player 2!");
      player2points++;
      player1points--;
      goBackward();
    }else
    if(choice1 == "scissor" && choice2 == "paper"){
      ROS_INFO("1p goes to Player 1!");
      player1points++;
      player2points--;
      goForward();
    }else
    if(choice1 == "paper" && choice2 == "scissor"){
      ROS_INFO("1p goes to Player 2!");
      player2points++;
      player1points--;
      goBackward();
    }else
    if(choice1 == "paper" && choice2 == "rock"){
      ROS_INFO("1p goes to Player 1!");
      player1points++;
      player2points--;
      goForward();
    }else
    if(choice1 == "rock" && choice2 == "paper"){
      ROS_INFO("1p goes to Player 2!");
      player2points++;
      player1points--;
      goBackward();
    }

    if(player1points == 3) {
      ROS_INFO("Game over! Player1 won!");
      stop = true;
      winSpin();
    }else if(player2points == 3) {
      ROS_INFO("Game over! Player2 won!");
      stop = true;
      winSpin();
    }
}
