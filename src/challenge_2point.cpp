#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <cmath>

geometry_msgs::Twist velocidade;
ros::Publisher pub_v;
double distance, x_final = 4, y_final = 1.5,x_atual,y_atual, theta,var_theta;


void callback(const nav_msgs::OdometryConstPtr &msg)
{
    geometry_msgs::Quaternion qt;
    x_atual = msg->pose.pose.position.x;
    y_atual = msg->pose.pose.position.y;
    qt = msg->pose.pose.orientation;
    double yaw = tf::getYaw(qt);
    double ang = yaw*180/M_PI;
    distance = sqrt(pow(x_final-x_atual,2)+ pow(y_final-y_atual,2));
    theta = atan((y_final-y_atual)/(x_final-x_atual))*180/M_PI;
    var_theta = theta - ang;
    if(var_theta > 180)//normalização
    {
        var_theta = var_theta - 360;
    }
    if(distance>0.2)
    {
        if(abs(var_theta)>0.7)
        {
            velocidade.linear.x = 0;
            velocidade.angular.z = 0.1*var_theta;
        }
        else
        {
            velocidade.linear.x = 0.5;
            velocidade.angular.z = 0;
        }
    }
    else
    {
        velocidade.linear.x = 0;
        velocidade.angular.z = 0;
    }
    pub_v.publish(velocidade);
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"go2po");
    ros::NodeHandle node;
    
    ros::Subscriber sub_odom = node.subscribe("/vrep/vehicle/odometry",1,callback);
    
    pub_v = node.advertise<geometry_msgs::Twist>("ros_odom",1);
    
    ros::spin();
    
}