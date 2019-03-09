#include <gohi_hw/HIGO_ROS.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "gohi_hw_imu");
    ros::NodeHandle nh("gohi_hw_imu");

    HIGO_ROS higo(nh, "serial:///dev/ttyUSB0", "/home/zhuxi/gohi_ws/src/GOHI_ROBOT/imu/gohi_hw_imu/config.txt");

    higo.mainloop();
    return 0;
}
