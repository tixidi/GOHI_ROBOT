#include <gohi_hw/HIGO_ROS.h>

 void HIGO_ROS::stair_cmd_callback(const gohi_msgs::stair_configConstPtr& msg)
 {
	std::cerr << "stair is  " << std::endl;
    higo_ap_.getRobotAbstract()->motor_pos_comp_state.posComp3=0;
	higo_ap_.getRobotAbstract()->stair_positionPhaseChange=msg->speed;
	higo_ap_.getRobotAbstract()->stair_type=msg->type;
	higo_ap_.getRobotAbstract()->stair_position=msg->position;
								  
 }


void HIGO_ROS::roll_cmd_callback(const gohi_msgs::roll_configConstPtr& msg)
 {
	higo_ap_.getRobotAbstract()->dilong_speed=msg->m1_speed; 
	std::cerr <<"roll ask speed  is " <<higo_ap_.getRobotAbstract()->dilong_speed<<std::endl;		
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
		robot_state_publisher_ = nh_.advertise<gohi_msgs::robot_state>("robot_state", 10);
		stair_cmd_subscribe_ = nh_.subscribe("/mobile_base/stair_controller/cmd_vel", 1,  &HIGO_ROS::stair_cmd_callback, this);
		roll_cmd_subscribe_ = nh_.subscribe("/mobile_base/roll_controller/cmd_vel", 1,  &HIGO_ROS::roll_cmd_callback, this);

		x_ = y_ = theta_ = x_cmd_ = y_cmd_ = theta_cmd_ = 0.0;
		x_vel_ = y_vel_ = theta_vel_ = 0.0;
        head_servo1_cmd_ = head_servo2_cmd_  =  0.0;
        head_servo1_pos_ = head_servo1_vel_ = head_servo1_eff_ = 0;
        head_servo2_pos_ = head_servo2_vel_ = head_servo2_eff_ = 0;


		//register the hardware interface on the robothw

		hardware_interface::BaseStateHandle    base_state_handle("mobile_base", &x_, &y_, &theta_, &x_vel_, &y_vel_, &theta_vel_);
		base_state_interface_.registerHandle(base_state_handle);
		hardware_interface::BaseVelocityHandle base_handle(base_state_handle, &x_cmd_, &y_cmd_, &theta_cmd_);
		base_velocity_interface_.registerHandle(base_handle);
	
  		registerInterface(&base_state_interface_);
		registerInterface(&base_velocity_interface_);

		if (base_mode_ == "3omni-wheel")
		{
		    wheel_pos_.resize(3, 0);
			wheel_vel_.resize(3, 0);
			wheel_eff_.resize(3, 0);
			wheel_cmd_.resize(3, 0);


			hardware_interface::JointStateHandle wheel1_state_handle("wheel_1", &wheel_pos_[0], &wheel_vel_[0], &wheel_eff_[0]);
			jnt_state_interface_.registerHandle(wheel1_state_handle);
			hardware_interface::JointHandle wheel1_handle(wheel1_state_handle, &wheel_cmd_[0]);
			base_vel_interface_.registerHandle(wheel1_handle);

			hardware_interface::JointStateHandle wheel2_state_handle("wheel_2", &wheel_pos_[1], &wheel_vel_[1], &wheel_eff_[1]);
			jnt_state_interface_.registerHandle(wheel2_state_handle);
			hardware_interface::JointHandle wheel2_handle(wheel2_state_handle, &wheel_cmd_[1]);
			base_vel_interface_.registerHandle(wheel2_handle);

			hardware_interface::JointStateHandle wheel3_state_handle("wheel_3", &wheel_pos_[2], &wheel_vel_[2], &wheel_eff_[2]);
			jnt_state_interface_.registerHandle(wheel3_state_handle);
			hardware_interface::JointHandle wheel3_handle(wheel3_state_handle, &wheel_cmd_[2]);
			base_vel_interface_.registerHandle(wheel3_handle);

			registerInterface(&jnt_state_interface_);
			registerInterface(&base_vel_interface_);
		}
        else if (base_mode_ == "2diff-wheel")
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
    		if (with_arm_)
    		{
				arm_pos_.resize(6,0);
				arm_cmd_.resize(6,0);
				
        		// for (int i = 0;i < 6;i++)
        		// {
            	// 		//get the joint name
            	// 	std::stringstream ss;
			    //     ss << "arm" << (i + 1)<<std::endl;
			    //     hardware_interface::JointStateHandle arm_state_handle(ss.str(), &arm_pos_[i], &arm_pos_[i], &arm_pos_[i]);
			    //     jnt_state_interface_.registerHandle(arm_state_handle);
            	// 	hardware_interface::JointHandle arm_handle(arm_state_handle , &arm_cmd_[i]);
            	// 	servo_pos_interface_.registerHandle(arm_handle);
                // }
				hardware_interface::JointStateHandle arm1_state_handle("arm1", &arm_pos_[0], &arm_pos_[0], &arm_pos_[0]);
			    jnt_state_interface_.registerHandle(arm1_state_handle);
            	hardware_interface::JointHandle arm1_handle(arm1_state_handle , &arm_cmd_[0]);
            	servo_pos_interface_.registerHandle(arm1_handle);

				hardware_interface::JointStateHandle arm2_state_handle("arm2", &arm_pos_[1], &arm_pos_[1], &arm_pos_[1]);
			    jnt_state_interface_.registerHandle(arm2_state_handle);
            	hardware_interface::JointHandle arm2_handle(arm2_state_handle , &arm_cmd_[1]);
            	servo_pos_interface_.registerHandle(arm2_handle);
				
				hardware_interface::JointStateHandle arm3_state_handle("arm3", &arm_pos_[2], &arm_pos_[2], &arm_pos_[2]);
			    jnt_state_interface_.registerHandle(arm3_state_handle);
            	hardware_interface::JointHandle arm3_handle(arm3_state_handle , &arm_cmd_[2]);
            	servo_pos_interface_.registerHandle(arm3_handle);
				
				hardware_interface::JointStateHandle arm4_state_handle("arm4", &arm_pos_[3], &arm_pos_[3], &arm_pos_[3]);
			    jnt_state_interface_.registerHandle(arm4_state_handle);
            	hardware_interface::JointHandle arm4_handle(arm4_state_handle , &arm_cmd_[3]);
            	servo_pos_interface_.registerHandle(arm4_handle);
				
				hardware_interface::JointStateHandle arm5_state_handle("arm5", &arm_pos_[4], &arm_pos_[4], &arm_pos_[4]);
			    jnt_state_interface_.registerHandle(arm5_state_handle);
            	hardware_interface::JointHandle arm5_handle(arm5_state_handle , &arm_cmd_[4]);
            	servo_pos_interface_.registerHandle(arm5_handle);
				
				hardware_interface::JointStateHandle arm6_state_handle("arm6", &arm_pos_[5], &arm_pos_[5], &arm_pos_[5]);
			    jnt_state_interface_.registerHandle(arm6_state_handle);
            	hardware_interface::JointHandle arm6_handle(arm6_state_handle , &arm_cmd_[5]);
            	servo_pos_interface_.registerHandle(arm6_handle);								
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
		ros::NodeHandle cm_nh("gohi_hw_power_car_mobile_base");
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

