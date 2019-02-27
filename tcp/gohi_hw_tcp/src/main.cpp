#include <gohi_hw/HIGO_ROS.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "gohi_hw_imu");
    ros::NodeHandle nh("gohi_hw_imu");

    HIGO_ROS higo(nh, "tcp", "/home/zhuxi/gohi_ws/src/GOHI_ROBOT/tcp/gohi_hw_tcp/config.txt");

    higo.mainloop();
    return 0;
}
