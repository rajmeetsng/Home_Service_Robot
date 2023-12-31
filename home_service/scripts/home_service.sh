#!/bin/sh

# Deploy turtlebot3 in custom Gazebo world
xterm  -e  " roslaunch home_service home_service_world.launch " &
sleep 10

# Launch amcl for localization
xterm -e " roslaunch home_service amcl.launch " &
sleep 5

# Launch rviz with saved configurations 
xterm  -e " roslaunch home_service view_navigation.launch" &
sleep 5

# Launch add_markers node to simulate package pick-up & drop-off   
xterm  -e " rosrun add_markers add_markers " &
sleep 2

# Launch pick_objects node to navigate to pick-up & drop-off zones  
xterm  -e " rosrun pick_objects pick_objects " 
