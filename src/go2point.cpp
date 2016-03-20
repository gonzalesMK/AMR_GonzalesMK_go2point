#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>

double yaw,y,x,teta;
geometry_msgs::Twist vel;
ros::Publisher  pub;

void callback(const nav_msgs::OdometryConstPtr& pos) {
      geometry_msgs::Quaternion qt;  
      qt = pos ->pose.pose.orientation ;
      yaw = tf::getYaw(qt);
      y = pos->pose.pose.position.y;
      x = pos->pose.pose.position.x;
      teta = atan2((1.5 - y) , ( -3 - x))  ;
      
    if ( abs(teta - yaw) > 3.14 ) {
         
        
    } 
    
      pub.publish(vel);
      std:: cout << teta << "   " << yaw << std::endl;
}

    
    int main(int argc, char **argv)
{  
    ros::init(argc,argv, "Go2Point");
    ros::NodeHandle node;
    
    pub = node.advertise<geometry_msgs::Twist>("/position_control", 1);
    ros::Subscriber position = node.subscribe("/vrep/vehicle/odometry", 1, callback);
    
    ros::spin();
    
    
}