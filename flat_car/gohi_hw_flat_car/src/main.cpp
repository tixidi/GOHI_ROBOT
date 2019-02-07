#include <gohi_hw/HIGO_ROS.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "flat_car_hw");
    ros::NodeHandle nh("flat_car");

    HIGO_ROS higo(nh, "serial:///dev/pts/18", "/home/wb/gohi_ws/src/GOHI_ROBOT/flat_car/gohi_hw_flat_car/config.txt");

    higo.mainloop();
    return 0;
}
