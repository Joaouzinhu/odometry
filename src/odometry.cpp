#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>

void callback(const nav_msgs::OdometryConstPtr &msg)
{
    geometry_msgs::Quaternion qt;
    qt = msg->pose.pose.orientation;
    double yaw = tf::getYaw(qt);
    std::cout << "Yaw: "<< yaw*180/M_PI<< std::endl;
}
int main(int argc, char** argv)
    
{
    ros::init(argc,argv,"Odomet");
    ros::NodeHandle nh;
    
    ros::Subscriber odom_sub = nh.subscribe("/vrep/vehicle/odometry",1,callback);
    ros::spin()
}