//
// Created by lyp on 21.09.20.
//

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);

    image_transport::Publisher pub = it.advertise("/mypublisher/left", 1);
    image_transport::Publisher pub1 = it.advertise("/mypublisher/right", 1);

    cv::Mat image = cv::imread("/home/lyp/1_Code/catkin_ws_1/src/test_receive_images/src/spongebob.jpg", 1);
    cv::Mat image1 = cv::imread("/home/lyp/1_Code/catkin_ws_1/src/test_receive_images/src/simpsons.jpg", 1);

//    cv::waitKey(30);
//    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
//    sensor_msgs::ImagePtr msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image1).toImageMsg();

    ros::Rate loop_rate(100);
    while (nh.ok()) {
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        sensor_msgs::ImagePtr msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image1).toImageMsg();
        pub.publish(msg);
        pub1.publish(msg1);
        ros::spinOnce();
        loop_rate.sleep();
    }
}