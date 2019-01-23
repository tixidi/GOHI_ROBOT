#include <gohi_hw/HIGO_ROS.h>


void HIGO_ROS::idcard_read_config_callback(const gohi_msgs::idcard_read_config& msg)
 {
	std::cerr << "idcard is  " << std::endl;

	higo_ap_.getRobotAbstract()->Temperature_Data.read_from_reg_data3=msg.data[0];
	higo_ap_.getRobotAbstract()->Temperature_Data.read_from_reg_data4 =msg.data[1];
	

	higo_ap_.getRobotAbstract()->laxian_length.length_data=msg.data[2];

	higo_ap_.getRobotAbstract()->rfid_read_data.singnal_intensity=msg.data[3];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_state=msg.data[4];
	higo_ap_.getRobotAbstract()->rfid_read_data.write_state=msg.data[5];

	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data1=msg.data[6];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data2=msg.data[7];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data3=msg.data[8];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data4=msg.data[9];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data5=msg.data[10];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data6=msg.data[11];    
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data7=msg.data[12];
	higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data8=msg.data[13];  


	higo_ap_.getRobotAbstract()->euler_angle.pitch=msg.data[14];
	higo_ap_.getRobotAbstract()->euler_angle.roll =msg.data[15];
	higo_ap_.getRobotAbstract()->euler_angle.yaw=msg.data[16];


	std::cerr <<"measure temp_for: " <<msg.data[0]<<"  'C" <<std::endl; 
	std::cerr <<"measure temp_back  " <<msg.data[1]  <<"  'C"<<std::endl;  
	std::cerr <<"measure Length: " <<msg.data[2]<<"  mm" <<std::endl; 


	std::cerr <<"measure singnal " <<msg.data[5]<<std::endl;   
	std::cerr <<"measure read_state  " <<msg.data[4]<<std::endl;   	
	std::cerr <<"measure write_state  " <<msg.data[3]<<std::endl; 

	std::cerr <<"ID1 interface   " <<msg.data[6]<<std::endl; 				  
	std::cerr <<"ID2 interface   " <<msg.data[7]<<std::endl; 
	std::cerr <<"ID3 interface   " <<msg.data[8]<<std::endl; 
	std::cerr <<"ID4 interface   " <<msg.data[9]<<std::endl; 
	std::cerr <<"ID5 interface   " <<msg.data[10]<<std::endl; 
	std::cerr <<"ID6 interface   " <<msg.data[11]<<std::endl; 
	std::cerr <<"ID7 interface   " <<msg.data[12]<<std::endl; 								
	std::cerr <<"ID8 interface   " <<msg.data[13]<<std::endl; 		


	std::cerr <<"measure pitch  " <<msg.data[14]  <<std::endl;  
	std::cerr <<"measure roll  " <<msg.data[15]<<std::endl;   
	std::cerr <<"measure yaw  " <<msg.data[16]<<std::endl;   

  	idcard_read_flag=1;
								  
 }

 void HIGO_ROS::laser_range_read_config_callback(const gohi_msgs::sick_range& msg)
 {
	std::cerr << "sick range is  " << std::endl;

    // memcpy(&msg.data[0],&higo_ap_.getRobotAbstract()->laser_scan_data[0],360);   
  	
	 for(int kk=0;kk<360;kk++) 
	  {
		  higo_ap_.getRobotAbstract()->laser_scan_data[kk]=msg.data[kk];
	  }
	  sick_range_read_flag=1;

								  
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
		// robot_state_publisher_ = nh_.advertise<gohi_msgs::robot_state>("robot_state", 10);
//      public more topics
		robot_cmd_publisher_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/mobile_base_controller/cmd_vel", 1000);
		stair_cmd_publisher_ = nh_.advertise<gohi_msgs::stair_config>("/mobile_base/stair_controller/cmd_vel", 1000);
		roll_cmd_publisher_ = nh_.advertise<gohi_msgs::roll_config>("/mobile_base/roll_controller/cmd_vel", 1000);
		idcard_write_config_publisher_ = nh_.advertise<gohi_msgs::idcard_write_config>("/idcard_write_config/cmd", 1000);
		laser_range_config_publisher_ = nh_.advertise<gohi_msgs::laser_range_config>("/laser_range_config/cmd", 1000);
		robot_desire_point_config_publisher_ = nh_.advertise<gohi_msgs::robot_desire_point_config>("/robot_desire_point_config/cmd", 1000);

		idcard_read_config_subscriber_ = nh_.subscribe("/idcard_read_config/cmd", 1,  &HIGO_ROS::idcard_read_config_callback, this);
		sick_range_read_config_subscriber_ = nh_.subscribe("/sick_range", 1,  &HIGO_ROS::laser_range_read_config_callback, this);


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
	    geometry_msgs::Twist twist;

		ros::NodeHandle cm_nh("mobile_base1");
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






           // car1 /car2  speed control    
          if(higo_ap_.getRobotAbstract()->receive_package_flag==1)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
				higo_ap_.updateCommand(READ_INTERFACE_CAR1_SPEED_CONTROL, count,3);//回传应答
				twist.linear.x = (float)higo_ap_.getRobotAbstract()->car1_speed_config.x_speed/100.0 ;
				twist.linear.y = (float)higo_ap_.getRobotAbstract()->car1_speed_config.y_speed/100.0;
				twist.linear.z = 0;
				twist.angular.x = 0;
				twist.angular.y = 0;
				twist.angular.z = (float)higo_ap_.getRobotAbstract()->car1_speed_config.z_speed/100.0;
        		std::cerr <<"car1 interface x_speed  " <<twist.linear.x <<std::endl; 
        		std::cerr <<"car1 interface y_speed  " <<twist.linear.y <<std::endl; 
        		std::cerr <<"car1 interface z_speed  " <<twist.angular.z<<std::endl; 				
				robot_cmd_publisher_.publish(twist);
		  }
		  //car3 position control
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==3)
		  {
				higo_ap_.getRobotAbstract()->receive_package_flag=0;
				higo_ap_.updateCommand(READ_INTERFACE_CAR3_POSITION_CONTROL, count,3);//回传应答				
				stair_vel_cmd_config_.speed = (float)higo_ap_.getRobotAbstract()->car3_position_config.speed/100.0 ;
				stair_vel_cmd_config_.type = (float)higo_ap_.getRobotAbstract()->car3_position_config.type ;
				stair_vel_cmd_config_.position = (float)higo_ap_.getRobotAbstract()->car3_position_config.position ;
				std::cerr <<"car3 interface speed  " <<stair_vel_cmd_config_.speed<<std::endl; 
        		std::cerr <<"car3 interface type  " <<stair_vel_cmd_config_.type<<std::endl; 
        		std::cerr <<"car3 interface position  " <<stair_vel_cmd_config_.position<<std::endl; 
 
				stair_cmd_publisher_.publish(stair_vel_cmd_config_);			  
		  }
		  // car4 -dilong speed_control
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==4)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
				higo_ap_.updateCommand(READ_INTERFACE_CAR4_SINGLE_SPEED_CONTROL, count,3);//回传应答					  
		   		roll_vel_cmd_config_.m1_speed = (float)higo_ap_.getRobotAbstract()->car4_single_speed_config.m1_speed/100.0 ;
		   		roll_vel_cmd_config_.m2_speed = (float)higo_ap_.getRobotAbstract()->car4_single_speed_config.m1_speed/100.0 ;
		   		roll_vel_cmd_config_.m3_speed = (float)higo_ap_.getRobotAbstract()->car4_single_speed_config.m1_speed/100.0 ;
		   		std::cerr <<"car4 interface m1_speed  " <<roll_vel_cmd_config_.m1_speed<<std::endl; 
        		std::cerr <<"car4 interface m2_speed  " <<roll_vel_cmd_config_.m2_speed<<std::endl; 
        		std::cerr <<"car4 interface m3_speed  " <<roll_vel_cmd_config_.m3_speed<<std::endl; 

    	   		roll_cmd_publisher_.publish(roll_vel_cmd_config_);			  
		  }
		  //car 1 -position feedback
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==5)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
				higo_ap_.updateCommand(READ_INTERFACE_CAR1_ODOM_CONTROL, count,3);//回传应答	
		   		robot_desire_point_config_.position_x = (float)higo_ap_.getRobotAbstract()->car_global_position_config.position_X/100.0;
		   		robot_desire_point_config_.position_y= (float)higo_ap_.getRobotAbstract()->car_global_position_config.position_Y/100.0 ;
		   		robot_desire_point_config_.position_z = (float)higo_ap_.getRobotAbstract()->car_global_position_config.position_Z/100.0 ;

				std::cerr <<"car1 X Position  " <<robot_desire_point_config_.position_x<<std::endl; 
				std::cerr <<"car1 Y Position  " <<robot_desire_point_config_.position_y<<std::endl; 
				std::cerr <<"car1 Z Position  " <<robot_desire_point_config_.position_z<<std::endl;  


    	   		robot_desire_point_config_publisher_.publish(robot_desire_point_config_);			  
		  }		  
		  // id  write control
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==6)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
				higo_ap_.updateCommand(READ_INTERFACE_ID_CONTROL, count,3);//回传应答		
				// higo_ap_.updateCommand(SET_RFID_REG_DATA, count,1);//射频传感器读卡  ---ok			  
				idcard_write_config_.data[0]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data1;
				idcard_write_config_.data[1]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data2;
				idcard_write_config_.data[2]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data7;
				idcard_write_config_.data[3]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data6;
				idcard_write_config_.data[4]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data4;
				idcard_write_config_.data[5]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data5;
				idcard_write_config_.data[6]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data3;
				idcard_write_config_.data[7]=(short int)higo_ap_.getRobotAbstract()->rfid_write_data.write_to_reg_data8;

				std::cerr <<"ID1 interface   " <<idcard_write_config_.data[0]<<std::endl; 
				std::cerr <<"ID2 interface   " <<idcard_write_config_.data[1]<<std::endl; 
				std::cerr <<"ID3 interface   " <<idcard_write_config_.data[2]<<std::endl; 
				std::cerr <<"ID4 interface   " <<idcard_write_config_.data[3]<<std::endl; 
				std::cerr <<"ID5 interface   " <<idcard_write_config_.data[4]<<std::endl; 
				std::cerr <<"ID6 interface   " <<idcard_write_config_.data[5]<<std::endl; 
				std::cerr <<"ID7 interface   " <<idcard_write_config_.data[6]<<std::endl; 
				std::cerr <<"ID8 interface   " <<idcard_write_config_.data[7]<<std::endl; 
				
    	   		idcard_write_config_publisher_.publish(idcard_write_config_);			  
		  }
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==7)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
	     		higo_ap_.updateCommand(READ_INTERFACE_LASER_CONTROL, count,3);//回传应答					  

				laser_range_config_.l_range=(short int)higo_ap_.getRobotAbstract()->laser_range_config.laser_range_L;
				laser_range_config_.r_range=(short int)higo_ap_.getRobotAbstract()->laser_range_config.laser_range_R;

				std::cerr <<"Laser range L  " <<laser_range_config_.l_range<<std::endl; 
				std::cerr <<"Laser range R  " <<laser_range_config_.r_range<<std::endl; 

                float temp_range=laser_range_config_.r_range-laser_range_config_.l_range;
        		if(temp_range>0)  
        		{
            		laser_range_config_.laser_scan_num=(unsigned short int)temp_range/0.5;
				}
				else    laser_range_config_.laser_scan_num=0;    
             
            	std::cerr <<"Laser scan num  " <<laser_range_config_.laser_scan_num<<std::endl; 
    	   		laser_range_config_publisher_.publish(laser_range_config_);			  
		  }
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==8)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
        	    higo_ap_.updateCommand(WRITE_SENSOR_DATA_TO_PAD_INTERFACE, count,3);//射频传感器读卡  ---ok				  	  
		  }
		  else  if(higo_ap_.getRobotAbstract()->receive_package_flag==9)
		  {
			  	higo_ap_.getRobotAbstract()->receive_package_flag=0;
        	    higo_ap_.updateCommand(WRITE_LASER_DATA_TO_PAD_INTERFACE, count,3);//射频传感器读卡  ---ok				  	  
		  }


			higo_ap_.updateCommand(READ_INTERFACE_CAR1_SPEED_CONTROL, count,2);//射频传感器读卡
			//----------------------------------------------------
			readBufferUpdate();

			cm.update(ros::Time::now(), ros::Duration(1 / controller_freq_));
            // ROS_INFO("head_servo1_cmd_ = %.4f  head_servo2_cmd_=%.4f" , head_servo1_cmd_ ,head_servo2_cmd_);

			writeBufferUpdate();
			 
			rate.sleep();
			
			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() << std::endl;
			// currentTime = ros::Time::now();
			count++;

			// std::cerr << "spend time is  " << (ros::Time::now() - currentTime).toSec() <<std::endl;
			// std::cerr << "count is  " <<  count<<std::endl;
			
			// currentTime = ros::Time::now();
		}

		cm_spinner.stop();
		hw_spinner.stop();

	}

