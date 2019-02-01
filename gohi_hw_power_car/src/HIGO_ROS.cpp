#include <gohi_hw/HIGO_ROS.h>



  void HIGO_ROS::brake_cmd_callback(const gohi_msgs::brake_configConstPtr& msg)
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
		robot_state_publisher_ = nh_.advertise<gohi_msgs::robot_state>("power_car_robot_state", 10);
		brake_cmd_subscribe_ = nh_.subscribe("/power_car_mobile_base/brake_cmd", 1,  &HIGO_ROS::brake_cmd_callback, this);

		x_ = y_ = theta_ = x_cmd_ = y_cmd_ = theta_cmd_ = 0.0;
		x_vel_ = y_vel_ = theta_vel_ = 0.0;
        head_servo1_cmd_ = head_servo2_cmd_  =  0.0;
        head_servo1_pos_ = head_servo1_vel_ = head_servo1_eff_ = 0;
        head_servo2_pos_ = head_servo2_vel_ = head_servo2_eff_ = 0;


		//register the hardware interface on the robothw

		hardware_interface::BaseStateHandle    base_state_handle("power_car_mobile_base", &x_, &y_, &theta_, &x_vel_, &y_vel_, &theta_vel_);
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


		hardware_interface::JointStateHandle head_servo1_state_handle("servo_1", &head_servo1_pos_, &head_servo1_vel_, &head_servo1_eff_);
	    jnt_state_interface_.registerHandle(head_servo1_state_handle);
    	hardware_interface::JointHandle head_servo1_handle(head_servo1_state_handle, &head_servo1_cmd_);
    	servo_pos_interface_.registerHandle(head_servo1_handle);

    	hardware_interface::JointStateHandle head_servo2_state_handle("servo_2", &head_servo2_pos_, &head_servo2_vel_, &head_servo2_eff_);
    	jnt_state_interface_.registerHandle(head_servo2_state_handle);
    	hardware_interface::JointHandle head_servo2_handle(head_servo2_state_handle, &head_servo2_cmd_);
    	servo_pos_interface_.registerHandle(head_servo2_handle);


		registerInterface(&jnt_state_interface_);
    	registerInterface(&servo_pos_interface_);
		
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
		ros::NodeHandle cm_nh("power_car_mobile_base");
		cm_nh.setCallbackQueue(&cm_callback_queue);
		controller_manager::ControllerManager cm(this, cm_nh);

		ros::AsyncSpinner cm_spinner(1, &cm_callback_queue);
		ros::AsyncSpinner hw_spinner(1, &queue_);
		ros::Rate rate(controller_freq_);
		cm_spinner.start();
		hw_spinner.start();

		int count = 0;
		ros::Time currentTime = ros::Time::now();
		while (ros::ok())
		{
			// // higo_ap_.checkHandshake();
			// if (higo_ap_.updateCommand(READ_SYSTEM_INFO, count))
			// {
			// 	std::cout << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			// 	currentTime = ros::Time::now();
			// 	robot_state_publisher_.publish(robot_state);
			// }


            //  if(roll_config_callback_flag==1)
			//  {
				 
			// 	 	roll_config_callback_flag=0;				 
			//  }

			//  if(stair_config_call_back_flag==1)
			//  {
			// 	 stair_config_call_back_flag=0;



			//  }

    
			// higo_ap_.updateCommand(READ_MOT1_ERROR_STATE, count,0);
			// std::cerr << "first is -------------------- " <<std::endl;

		    // higo_ap_.updateCommand(READ_MOT1_SPEED, count,0);				 
	 
			
			//higo_ap_.updateCommand(READ_MOT1_REAL_POSITION, count,0);		//读电机左轮的速度	
			//std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl; 
		   // higo_ap_.updateCommand(READ_MOT2_REAL_POSITION, count,0);	 	//读电机右轮的速度	 
			//std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			// higo_ap_.updateCommand(READ_MOT3_REAL_POSITION, count,0);	    //读升降电机的位置	 

		    // higo_ap_.updateCommand(READ_CAR2_MOTOR3_COMPLETE_STATE, count,0);//讀取刮板位置完成情況
			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			 //higo_ap_.updateCommand(READ_MOT4_SPEED, count,0);	//读取地龙速度
			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			// higo_ap_.updateCommand(READ_LAXIAN_POSITION, count,0);
			// higo_ap_.updateCommand(READ_EULER_ANGLE, count,0);

            higo_ap_.updateRobot();
		
			
			//----------------------------------------------------
			readBufferUpdate();

			cm.update(ros::Time::now(), ros::Duration(1 / controller_freq_));
            // ROS_INFO("head_servo1_cmd_ = %.4f  head_servo2_cmd_=%.4f" , head_servo1_cmd_ ,head_servo2_cmd_);

			writeBufferUpdate();

			// higo_ap_.updateCommand(READ_RFID_POSITION, count,0);//射频传感器读卡





		 	higo_ap_.updateCommand(SET_CAR1_LEFT_SPEED_CONTROL, count,1);
			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			higo_ap_.updateCommand(SET_CAR1_RIGHT_SPEED_CONTROL, count,1);		 
			//std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
  			higo_ap_.updateCommand(SET_CAR2_POSITION_CONTROL, count,1);
			//   std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
		    higo_ap_.updateCommand(SET_CAR2_SPEED_CONTROL, count,1); //设置地龙速度
			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;

			rate.sleep();
			
			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			// currentTime = ros::Time::now();
			count++;

			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() <<std::endl;
			 std::cerr << "count is---------------------------------------------------  " <<  count<<std::endl;
			
			currentTime = ros::Time::now();
		}

		cm_spinner.stop();
		hw_spinner.stop();

	}

