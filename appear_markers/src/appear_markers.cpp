#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <math.h>





int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers1");
  ros::NodeHandle n;

  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  visualization_msgs::Marker marker;
    
  uint32_t shape = visualization_msgs::Marker::CUBE;
  
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  
  marker.ns = "add_markers1";
  marker.id = 0;
  marker.type = shape;
  
  
  marker.pose.position.x = 2;
  marker.pose.position.y = 2;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  
  marker.lifetime = ros::Duration();
  
  if (ros::ok())
  {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
  
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Marker at the pickup location");
    ros::Duration(5.0).sleep();
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Hide marker at the pickup location");

    ros::Duration(5.0).sleep();
    
    marker.pose.position.x = 1;
    marker.pose.position.y = 4.5;
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("Marker at the dropoff location");
    ros::Duration(10.0).sleep();
    
    ros::spinOnce();
    }
   
}
    
