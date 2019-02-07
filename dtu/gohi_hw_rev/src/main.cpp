#include <gohi_hw/HIGO_ROS.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robothw");
    ros::NodeHandle nh("gohi");

    HIGO_ROS higo(nh, "serial:///dev/pts/19", "/home/wb/gohi_ws/src/GOHI_ROBOT/dtu/gohi_hw_rev/config.txt");

    higo.mainloop();
    return 0;
}
