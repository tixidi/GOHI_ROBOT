#include <gohi_hw/HIGO_ROS.h>

 void HIGO_ROS::brake_cmd_callback(const flat_car_msgs::brake_configConstPtr& msg)
 {
	std::cerr << "set brake  is ------------------------------- " << std::endl;
	// if(msg->brake_config==1)
	{
		brake_config_callback_flag=msg->brake_config;
		brake_config_callback_flag1=msg->brake_config;
		
	}								  
 }



HIGO_ROS::HIGO_ROS(ros::NodeHandle &nh, std::string url, std::string config_addr) :
		higo_ap_(url, config_addr),
		nh_(nh)
	{
		//get the parameter
		nh_.setCallbackQueue(&queue_);
        base_mode_ = "2diff-wheel";
		with_arm_ = false;
		controller_freq_ = 100;
		nh_.getParam("base_mode", base_mode_);
		nh_.getParam("with_arm", with_arm_);
		nh_.getParam("freq", controller_freq_);
		robot_state_publisher_ = nh_.advertise<flat_car_msgs::robot_state>("flat_car_robot_state", 10);
		brake_cmd_subscribe_ = nh_.subscribe("/flat_car_mobile_base/brake_cmd", 1,  &HIGO_ROS::brake_cmd_callback, this);

		x_ = y_ = theta_ = x_cmd_ = y_cmd_ = theta_cmd_ = 0.0;
		x_vel_ = y_vel_ = theta_vel_ = 0.0;

		//register the hardware interface on the robothw
		hardware_interface::BaseStateHandle    base_state_handle("flat_car_mobile_base", &x_, &y_, &theta_, &x_vel_, &y_vel_, &theta_vel_);
		base_state_interface_.registerHandle(base_state_handle);
		hardware_interface::BaseVelocityHandle base_handle(base_state_handle, &x_cmd_, &y_cmd_, &theta_cmd_);
		base_velocity_interface_.registerHandle(base_handle);
	
  		registerInterface(&base_state_interface_);
		registerInterface(&base_velocity_interface_);


        if (base_mode_ == "2diff-wheel")
           {
               wheel_pos_.resize(2,0);
               wheel_vel_.resize(2.0);
               wheel_eff_.resize(2,0);
               wheel_cmd_.resize(2,0);

               hardware_interface::JointStateHandle wheel1_state_handle("wheel1", &wheel_pos_[0], &wheel_vel_[0], &wheel_eff_[0]);
               jnt_state_interface_.registerHandle(wheel1_state_handle);
               hardware_interface::JointHandle wheel1_handle(wheel1_state_handle, &wheel_cmd_[0]);
               base_vel_interface_.registerHandle(wheel1_handle);

               hardware_interface::JointStateHandle wheel2_state_handle("wheel2", &wheel_pos_[1], &wheel_vel_[1], &wheel_eff_[1]);
               jnt_state_interface_.registerHandle(wheel2_state_handle);
               hardware_interface::JointHandle wheel2_handle(wheel2_state_handle, &wheel_cmd_[1]);
               base_vel_interface_.registerHandle(wheel2_handle);

               registerInterface(&jnt_state_interface_);
               registerInterface(&base_vel_interface_);

           }
	
 		if (higo_ap_.initialize_ok())
		{
			ROS_INFO("system initialized succeed, ready for communication");
		}
		else
		{
			ROS_ERROR("hf link initialized failed, please check the hardware");
		}

	}

	void HIGO_ROS::mainloop()
	{
		ros::CallbackQueue cm_callback_queue;
		ros::NodeHandle cm_nh("flat_car_mobile_base");
		cm_nh.setCallbackQueue(&cm_callback_queue);
		controller_manager::ControllerManager cm(this, cm_nh);

		ros::AsyncSpinner cm_spinner(1, &cm_callback_queue);
		ros::AsyncSpinner hw_spinner(1, &queue_);
		ros::Rate rate(controller_freq_);
		cm_spinner.start();
		hw_spinner.start();

		int count = 0;
		ros::Time currentTime = ros::Time::now();
		// float  per_circle_position =(360/120)*8*30;
		// float  degree_to_ = 0.017453f;
		// float  pid_t=0.1;
		while (ros::ok())
		{
    		// 	higo_ap_.updateCommand(READ_MOT1_ERROR_STATE, count,0);			
			// 	// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
			// 	// currentTime = ros::Time::now();
			// 	higo_ap_.updateCommand(READ_MOT2_ERROR_STATE, count,0);			
			// 	// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;

			// // // currentTime = ros::Time::now();			
			// 	higo_ap_.updateCommand(READ_MOT1_REAL_POSITION, count,0);		//读电机左轮的速度	
			// // 	// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;

				
			// 	higo_ap_.updateCommand(READ_MOT2_REAL_POSITION, count,0);	 	//读电机右轮的速度	 
			// // 	// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
				// currentTime = ros::Time::now();

			// float intervale_time= (ros::Time::now() - currentTime).toSec();
			// std::cerr <<(int)count<< "spend time is  " << intervale_time <<std::endl;
			// currentTime = ros::Time::now();

            // higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo1=  (higo_ap_.getRobotAbstract()->ask_measure_motor_position_dif.position1) * 360 / ( per_circle_position*0.145 )*degree_to_;
        	// std::cerr <<"电机1速度: " <<higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo1<<" rad/s" <<std::endl; //读电机1位置
            // higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo2=  (higo_ap_.getRobotAbstract()->ask_measure_motor_position_dif.position2) * 360 / ( per_circle_position*0.145 )*degree_to_;
        	// std::cerr <<"电机2速度: " <<higo_ap_.getRobotAbstract()->ask_measure_motor_speed.servo2<<" rad/s" <<std::endl; //读电机1位置

            higo_ap_.updateRobot();
		
		
			readBufferUpdate();

			cm.update(ros::Time::now(), ros::Duration(1 / controller_freq_));


			writeBufferUpdate();

            robot_state.motor1_error_state=higo_ap_.getRobotAbstract()->motor_error_state.error1 ;
			robot_state.motor2_error_state=higo_ap_.getRobotAbstract()->motor_error_state.error2 ;

			robot_state_publisher_.publish(robot_state);
			
			// std::cerr << "spend time is  " <<(int)brake_config_callback_flag << std::endl;
			// std::cerr << "spend time is  " <<(int)brake_config_callback_flag1 << std::endl;

			if(brake_config_callback_flag==1)
			{
				higo_ap_.updateCommand(SET_MOT2_BRAKE_STATE, count,1);	 	//brake car
				higo_ap_.updateCommand(SET_MOT1_BRAKE_STATE, count,1);	 	//brake car
			}
			else  	
			{
				higo_ap_.updateCommand(SET_CAR1_LEFT_SPEED_CONTROL, count,1);
				// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
				// currentTime = ros::Time::now();

				higo_ap_.updateCommand(SET_CAR1_RIGHT_SPEED_CONTROL, count,1);	
				// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
				//  currentTime = ros::Time::now();
			}

			rate.sleep();
			count++;
		}
		cm_spinner.stop();
		hw_spinner.stop();

	}

