#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

double px = 2.0;  //pickup point in x 
double py = 2.0;  //pickup point in y 
double dx = 1.0;  //dropoff point in x 
double dy = 4.5;  //dropoff point in x 

bool markerflagP = false;
bool markerflagD = false;
bool markerflagR = false;

void robotmovedCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    
  double X = msg->pose.pose.position.x;
  double Y = msg->pose.pose.position.y;
  // ROS_INFO("Received nav_msgs");

  double distToPickup = fabs(sqrt(pow(X - px, 2) + pow(Y - py, 2)));
  double distToDropoff = fabs(sqrt(pow(X - dx, 2) + pow(Y - dy, 2)));  

  if (distToPickup < 0.1) {
    markerflagP = true;
    ROS_INFO("Pickup location reached");
  }
  
  if (distToDropoff < 0.1) {
    markerflagD = true;
    ROS_INFO("Dropoff location reached");
  }
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber amcl_sub = n.subscribe("amcl_pose", 1000, robotmovedCallback);

  visualization_msgs::Marker marker;
  
  uint32_t shape = visualization_msgs::Marker::CUBE;

  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "cube";
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


  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  while (ros::ok())
  {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Subscriber to marker");
      sleep(1);
    }
    
    if (!markerflagP)
    {
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
    }
    else if (!markerflagD)
    {
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      if (!markerflagR){
        markerflagR = true;
        ROS_INFO("Wait here for picking up!");
        ros::Duration(5.0).sleep();
      }
    }
    else
    {
      marker.pose.position.x = 1;
      marker.pose.position.y = 4.5;
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
    }
    
    ros::spinOnce();
  }
}
