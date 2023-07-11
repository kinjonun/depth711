#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

void depthImageCallback(const sensor_msgs::Image::ConstPtr& msg)
{
    try
    {
        // 将ROS图像消息转换为OpenCV格式
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);

        // 获取图像中心点坐标
        int centerX = cv_ptr->image.cols / 2;
        int centerY = cv_ptr->image.rows / 2;

        // 获取中心点深度值
        uint16_t depth = cv_ptr->image.at<uint16_t>(centerY, centerX);

        // 打印中心点深度值
        ROS_INFO("Center depth: %u", depth);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "depth_center_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/camera/depth/image_raw", 1, depthImageCallback);

    ros::spin();

    return 0;
}



