#!/bin/sh

# Deploy turtlebot3 in custom Gazebo world
xterm  -e  " roslaunch home_service home_service_world.launch " &
sleep 15

# Launch amcl for localization
xterm -e " roslaunch home_service amcl.launch " &
sleep 5

# Launch rviz with saved configurations 
xterm  -e " roslaunch home_service view_navigation.launch" &
sleep 10

# Launch add_markers node to simulate package pick-up & drop-off   
xterm  -e " rosrun appear_markers appear_markers "
