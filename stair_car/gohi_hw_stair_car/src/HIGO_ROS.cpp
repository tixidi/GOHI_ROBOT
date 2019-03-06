#include <gohi_hw/HIGO_ROS.h>

 void HIGO_ROS::stair_cmd_callback(const stair_car_msgs::stair_configConstPtr& msg)
 {
	std::cerr << "stair is  " << std::endl;
    higo_ap_.getRobotAbstract()->motor_pos_comp_state.posComp3=0;
	higo_ap_.getRobotAbstract()->stair_positionPhaseChange=msg->speed;
	higo_ap_.getRobotAbstract()->stair_type=msg->type;
	higo_ap_.getRobotAbstract()->stair_position=msg->position;
								  
 }


void HIGO_ROS::roll_cmd_callback(const stair_car_msgs::roll_configConstPtr& msg)
 {
	higo_ap_.getRobotAbstract()->dilong_speed=msg->m1_speed; 
	std::cerr <<"roll ask speed  is " <<higo_ap_.getRobotAbstract()->dilong_speed<<std::endl;		
 }

 void HIGO_ROS::brake_cmd_callback(const stair_car_msgs::brake_configConstPtr& msg)
 {
	std::cerr << "set brake  is ------------------------------- " << std::endl;
	// if(msg->brake_config==1)
	{
		brake_config_callback_flag=msg->brake_config;

		
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
		controller_freq_ = 50;
		nh_.getParam("base_mode", base_mode_);
		nh_.getParam("with_arm", with_arm_);
		nh_.getParam("freq", controller_freq_);
		robot_state_publisher_ = nh_.advertise<stair_car_msgs::robot_state>("stair_car_robot_state", 10);
		stair_cmd_subscribe_ = nh_.subscribe("/stair_car_mobile_base/stair_controller/cmd_vel", 1,  &HIGO_ROS::stair_cmd_callback, this);
		roll_cmd_subscribe_ = nh_.subscribe("/stair_car_mobile_base/roll_controller/cmd_vel", 1,  &HIGO_ROS::roll_cmd_callback, this);
		brake_cmd_subscribe_ = nh_.subscribe("/stair_car_mobile_base/brake_cmd", 1,  &HIGO_ROS::brake_cmd_callback, this);

		x_ = y_ = theta_ = x_cmd_ = y_cmd_ = theta_cmd_ = 0.0;
		x_vel_ = y_vel_ = theta_vel_ = 0.0;


		//register the hardware interface on the robothw

		hardware_interface::BaseStateHandle    base_state_handle("stair_car_mobile_base", &x_, &y_, &theta_, &x_vel_, &y_vel_, &theta_vel_);
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
		ros::NodeHandle cm_nh("stair_car_mobile_base");
		cm_nh.setCallbackQueue(&cm_callback_queue);
		controller_manager::ControllerManager cm(this, cm_nh);

		ros::AsyncSpinner cm_spinner(1, &cm_callback_queue);
		ros::AsyncSpinner hw_spinner(1, &queue_);
		ros::Rate rate(controller_freq_);
		cm_spinner.start();
		hw_spinner.start();

		int count = 0;
		ros::Time currentTime = ros::Time::now();

        static int command_switch_counts=0;




		while (ros::ok())
		{


     		std::cerr <<"-------------------------------------------------------------------------------" <<std::endl;

			switch(command_switch_counts%6)
			{					   
				case 0:
						higo_ap_.updateCommand(READ_MOT3_REAL_POSITION, count,0);	       
						break;
				case 1:		
						higo_ap_.updateCommand(READ_CAR2_MOTOR3_COMPLETE_STATE, count,0);	
				    	break;
						
				case 2:
						higo_ap_.updateCommand(READ_MOT3_ERROR_STATE, count,0);	
						break;
				case 3:		
						higo_ap_.updateCommand(READ_MOT4_ERROR_STATE, count,0);	
					    break;
				
				case 4:
						if(brake_config_callback_flag==1)
						{
							higo_ap_.updateCommand(SET_MOT3_BRAKE_STATE, count,1);	 	//brake car
						}
						else  	
						{
							higo_ap_.updateCommand(SET_CAR2_POSITION_CONTROL, count,1);
						}
				       break;
				case 5:
						if(brake_config_callback_flag==1)
						{
							higo_ap_.updateCommand(SET_MOT4_BRAKE_STATE, count,1);	 	//brake car			
						}
						else  	
						{
							higo_ap_.updateCommand(SET_CAR2_SPEED_CONTROL, count,1);	
						}
				       break;						

			}
			command_switch_counts++;

		
			readBufferUpdate();

			cm.update(ros::Time::now(), ros::Duration(1 / controller_freq_));


			writeBufferUpdate();

            robot_state.motor3_error_state=higo_ap_.getRobotAbstract()->motor_error_state.error3 ;
			robot_state.motor4_error_state=higo_ap_.getRobotAbstract()->motor_error_state.error4 ;

			robot_state_publisher_.publish(robot_state);
			
			std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
			currentTime = ros::Time::now();

			rate.sleep();

			count++;


		}

		cm_spinner.stop();
		hw_spinner.stop();

	}

