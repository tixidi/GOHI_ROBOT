#include <gohi_hw/HIGO_ROS.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robothw");
    ros::NodeHandle nh("gohi");

    HIGO_ROS higo(nh, "serial:///dev/ttyUSB1", "/home/zhuxi/gohi_ws/src/GOHI_ROBOT/gohi_hw_rev/config.txt");

    higo.mainloop();
    return 0;
}
