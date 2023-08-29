#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "pick_object");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  // Pick - Up action
  
  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 2.0;
  goal.target_pose.pose.position.y = 2.0;
  goal.target_pose.pose.orientation.w = 1.57;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, Robot reached at Pick Location");
  else
    ROS_INFO("The base failed to move for some reason");
  
  ros::Duration(5).sleep();
  
  while(!ac.waitForServer(ros::Duration(5.0))){
  	ROS_INFO("Waiting for the move_base action");
  }
  
  // Drop - Up action
  
  move_base_msgs::MoveBaseGoal goal2;

  //we'll send a goal to the robot to move 1 meter forward
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();

  goal2.target_pose.pose.position.x = 1.0;
  goal2.target_pose.pose.position.y = 4.5;
  goal2.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal2");
  ac.sendGoal(goal2);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, Robot reached at Drop Location");
  else
    ROS_INFO("The base failed to move for some reason");
  
  ros::Duration(5).sleep();
  

  return 0;
}
