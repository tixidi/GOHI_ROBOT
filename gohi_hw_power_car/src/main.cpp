#include <gohi_hw/HIGO_ROS.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robothw");
    ros::NodeHandle nh("gohi");

    HIGO_ROS higo(nh, "serial:///dev/ttyUSB2", "/home/zhuxi/gohi_ws/src/GOHI_ROBOT/gohi_hw_power_car/config.txt");

    higo.mainloop();
    return 0;
}
