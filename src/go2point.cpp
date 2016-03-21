#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>

double yaw,yi,xi,teta, delta,xf,yf;
geometry_msgs::Twist vel;
ros::Publisher  pub;

double norma_ang( double ang )
{   if  ( ang >  M_PI) {
        ang -= 2 * M_PI; 
    }
    else if ( ang < - M_PI){
        ang += 2 * M_PI;
    }
    return ang;
}

void callback(const nav_msgs::OdometryConstPtr& pos) {
      geometry_msgs::Quaternion qt;  
      qt = pos ->pose.pose.orientation ;
      yaw = tf::getYaw(qt);
      yi = pos->pose.pose.position.y;
      xi = pos->pose.pose.position.x;
      teta = atan2((yf - yi) , ( xf - xi));
      delta = norma_ang( (teta-yaw) );
      
      if ( fabs(delta) > 0.2 ){
        vel.angular.z = delta * 3;
        vel.linear.x =(M_PI - fabs(delta))*0.4 ;
      } else {
        vel.angular.z = delta*2 ;
        vel.linear.x = 3;
     }
     pub.publish(vel);
}

void Endback(const nav_msgs::OdometryConstPtr& posi){
    yf = posi->pose.pose.position.y;
    xf = posi->pose.pose.position.x;
}

    int main(int argc, char **argv)
{  
    ros::init(argc,argv, "Go2Point");
    ros::NodeHandle node;
    
    pub = node.advertise<geometry_msgs::Twist>("/position_control", 1);
    ros::Subscriber position = node.subscribe("/vrep/vehicle/odometry", 1, callback);
    ros::Subscriber end = node.subscribe("/vrep/vehicle/End", 1, Endback);    
    
    ros::spin();
    
    
}