#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "opencv4/opencv2/core.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include <cv_bridge/cv_bridge.h>


void msgCallback(const sensor_msgs::Image::ConstPtr& msg)
{
//    ROS_INFO("height = %d, width = %d",msg->height, msg->width);
    try
    {
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }


}
int main(int argc, char** argv)
{
    ros::init(argc,argv,"cam_data");
    ros::NodeHandle nh;

    ros::Subscriber cam_sub = nh.subscribe("/stereo/left/image_raw",100,msgCallback);
    ros::spin();

    return 0;
}