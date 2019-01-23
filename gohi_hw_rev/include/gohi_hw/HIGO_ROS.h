#ifndef HIGO_ROS_
#define HIGO_ROS_

#include <vector>
#include <string>
#include <sstream>
#include <iostream> 



#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

#include <gohi_hw/base_cmd_interface.h>
#include <gohi_hw/base_state_interface.h>


#include <hardware_interface/joint_state_interface.h>   //ref diffbot.h
#include <hardware_interface/joint_command_interface.h> //ref diffbot.h
#include <hardware_interface/robot_hw.h>                //ref diffbot.h
#include <realtime_tools/realtime_publisher.h>
#include <controller_manager/controller_manager.h>      //ref diffbot.h


#include <gohi_msgs/robot_state.h>
#include <gohi_msgs/roll_config.h>
#include <gohi_msgs/stair_config.h>
#include <gohi_msgs/idcard_read_config.h>
#include <gohi_msgs/idcard_write_config.h>
#include <gohi_msgs/laser_range_config.h>
#include <gohi_msgs/robot_desire_point_config.h>
#include <gohi_msgs/sick_range.h>



// for ros headers
#include <ros/ros.h>
#include <ros/callback_queue.h>

// for hf link and transport
#include <gohi_hw/transport.h>
#include <gohi_hw/transport_serial.h>
// #include <hf_link.h>
#include <hf_link_modbus.h>

#include <gohi_hw/HIGO_AP.h>
#include <LMS1xx/LMS1xx.h>



class HIGO_ROS : public  hardware_interface::RobotHW
{

public:
	HIGO_ROS(ros::NodeHandle &nh, std::string url, std::string config_addr);
    double getFreq()const
    {
       	return controller_freq_;
    }
	void mainloop();

private:
	//communication with embeded system
	HIGO_AP higo_ap_;
	ros::NodeHandle nh_;
	ros::CallbackQueue queue_;
	// publish the robot state for diagnose system
	ros::Publisher robot_state_publisher_;

	ros::Publisher robot_cmd_publisher_;
	ros::Publisher stair_cmd_publisher_;
	ros::Publisher roll_cmd_publisher_;

	ros::Publisher idcard_write_config_publisher_;
	ros::Publisher laser_range_config_publisher_;
	ros::Publisher robot_desire_point_config_publisher_;

    ros::Subscriber idcard_read_config_subscriber_;
	ros::Subscriber sick_range_read_config_subscriber_;
	
	


	ros::ServiceServer getparam_srv_;
	ros::ServiceServer setparam_srv_;

	//parameter list
	std::string base_mode_;
	bool with_arm_;
	double controller_freq_;

	//hardware resource
	gohi_msgs::robot_state robot_state;
	gohi_msgs::roll_config roll_vel_cmd_config_ ;
	gohi_msgs::stair_config stair_vel_cmd_config_;
			
	gohi_msgs::idcard_write_config idcard_write_config_;
	gohi_msgs::idcard_read_config idcard_read_config_;
	gohi_msgs::laser_range_config laser_range_config_;
	gohi_msgs::robot_desire_point_config robot_desire_point_config_;

	

	unsigned char idcard_read_flag;
	unsigned char sick_range_read_flag;
	
    std::vector<double> wheel_pos_, wheel_vel_, wheel_eff_, wheel_cmd_;
    std::vector<double> arm_pos_  , arm_vel_  , arm_eff_, arm_cmd_;
    double x_, y_, theta_, x_cmd_, y_cmd_, theta_cmd_;
    double x_vel_, y_vel_, theta_vel_;

    double head_servo1_pos_, head_servo1_vel_, head_servo1_eff_;
    double head_servo2_pos_, head_servo2_vel_, head_servo2_eff_;
    double head_servo1_cmd_, head_servo2_cmd_;


    hardware_interface::PositionJointInterface servo_pos_interface_;
	//ref   ����diffbot.h 
	//ref   ����diffbot.h 
	//ref 2 ����/opt/ros/indigo/include/hardware_interface/joint_state_interface.h 
	hardware_interface::JointStateInterface jnt_state_interface_;//wheel_pos_, wheel_vel_, wheel_eff_, 
	//ref 1 ����diffbot.h  
	//ref 2 ����/opt/ros/indigo/include/hardware_interface/joint_command_interface.h    
	// hardware_interface::PositionJointInterface servo_pos_interface_; 
	hardware_interface::VelocityJointInterface base_vel_interface_;//wheel_cmd_;

	hardware_interface::BaseStateInterface     base_state_interface_;// x_, y_, theta_,x_vel_, y_vel_, theta_vel_;
	hardware_interface::BaseVelocityInterface  base_velocity_interface_;// x_cmd_, y_cmd_, theta_cmd_;

	inline void writeBufferUpdate()
	{
		// higo_ap_.getRobotAbstract()->expect_motor_speed.servo1 = wheel_cmd_[0];
		// higo_ap_.getRobotAbstract()->expect_motor_speed.servo2 = wheel_cmd_[1];
		// higo_ap_.getRobotAbstract()->expect_motor_speed.servo3 = wheel_cmd_[2];
		// higo_ap_.getRobotAbstract()->ask_expect_motor_speed.servo1 = wheel_cmd_[0];//同机器人速度冲突，2选1
		// higo_ap_.getRobotAbstract()->ask_expect_motor_speed.servo2 = wheel_cmd_[1];
		// higo_ap_.getRobotAbstract()->ask_expect_motor_speed.servo3 = wheel_cmd_[2];

		higo_ap_.getRobotAbstract()->expect_robot_speed.x = x_cmd_;
		higo_ap_.getRobotAbstract()->expect_robot_speed.y = y_cmd_;
		higo_ap_.getRobotAbstract()->expect_robot_speed.z = theta_cmd_;

        if (with_arm_)
        {
           		higo_ap_.getRobotAbstract()->expect_arm_state.servo1 = arm_cmd_[0];
           		higo_ap_.getRobotAbstract()->expect_arm_state.servo2 = arm_cmd_[1];
		        higo_ap_.getRobotAbstract()->expect_arm_state.servo3 = arm_cmd_[2];
           		higo_ap_.getRobotAbstract()->expect_arm_state.servo4 = arm_cmd_[3];
           		higo_ap_.getRobotAbstract()->expect_arm_state.servo5 = arm_cmd_[4];
           		higo_ap_.getRobotAbstract()->expect_arm_state.servo6 = arm_cmd_[5];
        }
        // the servo num is different
        higo_ap_.getRobotAbstract()->expect_head_state.pitch  = head_servo1_cmd_;
        higo_ap_.getRobotAbstract()->expect_head_state.yaw    = head_servo2_cmd_;

	}

	inline void readBufferUpdate()
	{
		x_ = higo_ap_.getRobotAbstract()->measure_global_coordinate.x;
		y_ = higo_ap_.getRobotAbstract()->measure_global_coordinate.y;
		theta_ = higo_ap_.getRobotAbstract()->measure_global_coordinate.z;

		x_vel_ = higo_ap_.getRobotAbstract()->measure_robot_speed.x;       //
		y_vel_ = higo_ap_.getRobotAbstract()->measure_robot_speed.y;
		theta_vel_ = higo_ap_.getRobotAbstract()->measure_robot_speed.z;

		wheel_pos_[0] = higo_ap_.getRobotAbstract()->measure_motor_mileage.servo1;
		wheel_pos_[1] = higo_ap_.getRobotAbstract()->measure_motor_mileage.servo2;
		wheel_pos_[2] = higo_ap_.getRobotAbstract()->measure_motor_mileage.servo3;

        robot_state.battery_voltage = higo_ap_.getRobotAbstract()->system_info.battery_voltage;
        robot_state.cpu_temperature = higo_ap_.getRobotAbstract()->system_info.cpu_temperature;
        robot_state.cpu_usage = higo_ap_.getRobotAbstract()->system_info.cpu_usage;
        robot_state.system_time = higo_ap_.getRobotAbstract()->system_info.system_time;


        if (with_arm_)
        {
        	arm_pos_[0] = higo_ap_.getRobotAbstract()->measure_arm_state.servo1;
            arm_pos_[1] = higo_ap_.getRobotAbstract()->measure_arm_state.servo2;
            arm_pos_[2] = higo_ap_.getRobotAbstract()->measure_arm_state.servo3;
            arm_pos_[3] = higo_ap_.getRobotAbstract()->measure_arm_state.servo4;
            arm_pos_[4] = higo_ap_.getRobotAbstract()->measure_arm_state.servo5;
            arm_pos_[5] = higo_ap_.getRobotAbstract()->measure_arm_state.servo6;
        }

		// wheel_vel_[0] = higo_ap_.getRobotAbstract()->measure_motor_speed.servo1;
		// wheel_vel_[1] = higo_ap_.getRobotAbstract()->measure_motor_speed.servo2;
		// wheel_vel_[2] = higo_ap_.getRobotAbstract()->measure_motor_speed.servo3;
		wheel_vel_[0] = higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo1;
		wheel_vel_[1] = higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo2;
		wheel_vel_[2] = higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo3;
		
        // wheel_eff_[0] = 5;
		// wheel_eff_[1] = 6;
		// wheel_eff_[2] = 7;
		
		
		head_servo1_pos_ = higo_ap_.getRobotAbstract()->measure_head_state.pitch ;
        // head_servo1_vel_ = 1 ;
        // head_servo1_eff_ = 2 ;

        head_servo2_pos_ = higo_ap_.getRobotAbstract()->measure_head_state.yaw ;
        // head_servo2_vel_ = 3 ;
		// head_servo2_eff_ = 4 ;

	}
	void idcard_read_config_callback(const gohi_msgs::idcard_read_config& msg);
	void laser_range_read_config_callback(const gohi_msgs::sick_range& msg);
	

};




#endif
