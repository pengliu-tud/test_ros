

#include "show_images.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Image.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace sensor_msgs;
using namespace message_filters;

void imageCallback(const sensor_msgs::ImageConstPtr& left_msg, const sensor_msgs::ImageConstPtr& right_msg)
{
    try
    {
        ROS_INFO("111");
        auto img1 = cv_bridge::toCvShare(left_msg, "bgr8");
        auto img2 = cv_bridge::toCvShare(right_msg, "bgr8");
//        cv::imshow("view1", img1->image);
//        cv::imshow("view2", img2->image);

        cv::Mat img_merged;

        cv::addWeighted(img1->image, 0.5, img2->image, 0.5, 0, img_merged);
        cv::imshow("merged", img_merged);

//        cv::imshow("source", cv_bridge::toCvShare(right_msg, "bgr8")->image);

//        cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", left_msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener_merged");
    ros::NodeHandle nh;

//    cv::namedWindow("view1");
//    cv::namedWindow("view2");
    cv::startWindowThread();
//    image_transport::ImageTransport it(nh);
//    image_transport::Subscriber sub_right = it.subscribe("/stereo/right/image_raw", 100, imageCallback);
//    image_transport::Subscriber sub_left = it.subscribe("/stereo/left/image_raw", 100, imageClback);

    message_filters::Subscriber<sensor_msgs::Image> sub_left(nh, "/stereo/left/image_raw", 100);
    message_filters::Subscriber<sensor_msgs::Image> sub_right(nh, "/stereo/right/image_raw", 100);

//    message_filters::Subscriber<sensor_msgs::Image> source(nh, "/image_publisher_1600621054318491934/image_raw", 100);

    typedef sync_policies::ApproximateTime<Image, Image, Image> MySyncPolicy;
    // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
    Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), sub_left, sub_right);
//    sync.registerCallback([](auto && PH1, auto && PH2) { return imageCallback(PH1, PH2); });
    sync.registerCallback(boost::bind(&imageCallback, _1, _2));
    ROS_INFO("222");

    ros::spin();
    cv::destroyWindow("merged");
}