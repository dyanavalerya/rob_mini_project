#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Int16.h>
#include "std_msgs/Bool.h"
#include <string.h>
#include <iostream>

std::string choice1 = "choice1";
std::string choice2 = "choice2";
int player1points = 0, player2points = 0;
bool stop = false;
//ros::Publisher finish;

// Prototype functions
void gameCallback1(const std_msgs::String::ConstPtr& msg);
void gameCallback2(const std_msgs::String::ConstPtr& msg);
void compare(ros::Publisher publisher);


int main(int argc, char **argv){

  ros::init(argc, argv, "core");
  ros::NodeHandle nh;
  ros::Subscriber sub1 = nh.subscribe("choice1", 20, gameCallback1);
  ros::Subscriber sub2 = nh.subscribe("choice2", 20, gameCallback2);
  ros::Publisher finish = nh.advertise<std_msgs::Bool>("/finish", 10);

  ros::Duration(1.0).sleep();

  while(ros::ok() && !stop){
  ros::spinOnce();
    if(choice1 != "choice1" && choice2 != "choice2"){
      compare(finish);
      choice1 = "choice1";
      choice2 = "choice2";
    }
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

void compare(ros::Publisher publisher){

    if(choice1 == "rock" && choice2 == "scissor") {
      ROS_INFO("1p goes to Player 1!");
      player1points++;
      player2points--;
    }else
    if(choice1 == "scissor" && choice2 == "rock"){
      ROS_INFO("1p goes to Player 2!");
      player2points++;
      player1points--;
    }else
    if(choice1 == "scissor" && choice2 == "paper"){
      ROS_INFO("1p goes to Player 1!");
      player1points++;
      player2points--;
    }else
    if(choice1 == "paper" && choice2 == "scissor"){
      ROS_INFO("1p goes to Player 2!");
      player2points++;
      player1points--;
    }else
    if(choice1 == "paper" && choice2 == "rock"){
      ROS_INFO("1p goes to Player 1!");
      player1points++;
      player2points--;
    }else
    if(choice1 == "rock" && choice2 == "paper"){
      ROS_INFO("1p goes to Player 2!");
      player2points++;
      player1points--;
    }

    std_msgs::Bool stop2;


    if(player1points == 3) {
      ROS_INFO("Game over! Player1 won!");
      stop = true;
      stop2.data = stop;
      publisher.publish(stop2);
    }else if(player2points == 3) {
      ROS_INFO("Game over! Player2 won!");
      stop = true;
      stop2.data = stop;
      publisher.publish(stop2);
    }
}
