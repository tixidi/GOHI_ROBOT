#include <gohi_hw/HIGO_ROS.h>

 void HIGO_ROS::stair_cmd_callback(const stair_car_msgs::stair_configConstPtr& msg)
 {
	 if(update_data_cmd){
		 // std::cerr << "stair is  " << std::endl;
		if(higo_ap_.stair_position_temp == msg->position )
		{
			return;
		}
		else if((higo_ap_.stair_position_temp ==40.0)&&(msg->position>40.0))
		{
			return;
		}
		allow_set_stair_position_flag =1;
		update_data_cmd =0;
		higo_ap_.stair_position_complete_state =0;
		SQ_reset_not_allow_set_position =0;
		if(msg->position > 40.0)
		{
			higo_ap_.getRobotAbstract()->motor_pos_comp_state.posComp3=0;
			higo_ap_.getRobotAbstract()->stair_positionPhaseChange=msg->speed;
			higo_ap_.getRobotAbstract()->stair_type=msg->type;
			higo_ap_.getRobotAbstract()->stair_position=40.0;
			return;
		}
		higo_ap_.getRobotAbstract()->motor_pos_comp_state.posComp3=0;
		higo_ap_.getRobotAbstract()->stair_positionPhaseChange=msg->speed;
		higo_ap_.getRobotAbstract()->stair_type=msg->type;
		higo_ap_.getRobotAbstract()->stair_position=msg->position;
	 }
	
									  
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
		controller_freq_ = 20;  //修改前的数值为50
		nh_.getParam("base_mode", base_mode_);
		nh_.getParam("with_arm", with_arm_);
		nh_.getParam("freq", controller_freq_);
		robot_state_publisher_ = nh_.advertise<stair_car_msgs::robot_state>("stair_car_robot_state", 10);
		relay_state_publisher_ = nh_.advertise<stair_car_msgs::relay_state>("/relay_state_cmd", 1000);  //发布控制继电器命令
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

	void HIGO_ROS::delay(int time)
	{
		while(time--);
	}
	void HIGO_ROS::init()
	{
		while(1){
			higo_ap_.getRobotAbstract()->motor_pos_comp_state.posComp3=0;
			higo_ap_.getRobotAbstract()->stair_positionPhaseChange=2;
			higo_ap_.getRobotAbstract()->stair_type=0;
			higo_ap_.getRobotAbstract()->stair_position =-30.0;
			higo_ap_.updateCommand(SET_CAR2_POSITION_CONTROL, count,1);
			delay(500000000);
			higo_ap_.updateCommand(READ_CAR2_MOTER3_RESET_STATE, count,0);	
				if(!higo_ap_.stair_reset_SQ_state)
				{
					//行程开关触发
					SQ_reset_not_allow_set_position =1;
					update_data_cmd =1;
					relay_state =STAIR_RELAY6_ON; 
					higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38
					std::cerr << "push on"<<std::endl;
					break;	
				}
			delay(500000000);
		}
		std::cerr << "push" <<std::endl;
		delay(500000000);
		
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

		int rev_time_out_ =500;
		 count = 0;
		ros::Time currentTime = ros::Time::now();
		int test_flag =1;
        static int command_switch_counts=0;
		allow_set_stair_position_flag =0;
		SQ_reset_not_allow_set_position =0;
		start_flag =1;
		static int  time_cnt =0;
		update_data_cmd =1;
		relay_state =0x00;  //默认高三位为000   1表示ON   0表示off   每一位对应一个继电器
		relay_state =STAIR_RELAY6_OFF; 
		higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38		
		// init();	
		// delay(500000000);
		higo_ap_.updateCommand(SET_MOT3_RESET_TEST, count,1);	 	//对SQ2写复位测试	 
		delay(500000000);
		while (ros::ok())
		{
			// higo_ap_.updateCommand(SET_MOT3_RESET_TEST, count,1);	 	//对SQ2写复位测试
			higo_ap_.updateCommand(READ_CAR2_MOTOR3_COMPLETE_STATE, count,0);
			if(higo_ap_.stair_position_complete_state)
			{
				if(test_flag)
				{
					test_flag =0;
					std::cerr <<"higo_ap_.stair_position_complete_state =" <<(float)higo_ap_.getRobotAbstract()->stair_position<<std::endl;
				}
				time_cnt =0;
				update_data_cmd =1;
				relay_state =STAIR_RELAY6_OFF; 
				higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38

			}
			if(++time_cnt >= 400){

				update_data_cmd =1;
				time_cnt =0;
				higo_ap_.updateCommand(SET_MOT3_BRAKE_STATE, count,1);
				//relay_state =STAIR_RELAY6_ON; 
				//higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38

			}		
			if(higo_ap_.error_state)
			{	
				update_data_cmd =1;
				higo_ap_.error_state =0;
				// relay_state =STAIR_R-10.0ELAY6_ON; 
				// higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38	
			}
			switch(command_switch_counts%6)
			{					   
				case 0:
						higo_ap_.updateCommand(READ_MOT3_REAL_POSITION, count,0);	       
						break;
				// case 1:		
											
				//     	break;
						
				case 1:
						higo_ap_.updateCommand(READ_MOT3_ERROR_STATE, count,0);	
						break;
				case 2:		
						higo_ap_.updateCommand(READ_MOT4_ERROR_STATE, count,0);	
					    break;
				
				case 3:
						if(brake_config_callback_flag==1)
						{
							higo_ap_.updateCommand(SET_MOT3_BRAKE_STATE, count,1);	 	//brake car
						}
						else  	
						{
							if(allow_set_stair_position_flag)
							{
								test_flag =1;
								allow_set_stair_position_flag =0;
								relay_state =STAIR_RELAY6_ON;
								higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38
								// higo_ap_.updateCommand(SET_CAR2_POSITION_CONTROL, count,1);
							}
							
							if(!SQ_reset_not_allow_set_position)
								// std::cerr<<"into _______________________________"<<std::endl;
								 higo_ap_.updateCommand(SET_CAR2_POSITION_CONTROL, count,1);
						}
				       break;
				case 4:
						if(brake_config_callback_flag==1)
						{
							higo_ap_.updateCommand(SET_MOT4_BRAKE_STATE, count,1);	 	//brake car			
						}
						else  	
						{
							higo_ap_.updateCommand(SET_CAR2_SPEED_CONTROL, count,1);	
						}
				       break;	
				 case 5:
				 	  	higo_ap_.updateCommand(READ_CAR2_MOTER3_RESET_STATE, count,0);	
						if(!higo_ap_.stair_reset_SQ_state)
						{
							higo_ap_.updateCommand(SET_MOT3_RESET_TEST, count,1);	 	//对SQ2写复位测试
							// delay(500000000);
							//行程开关触发
							SQ_reset_not_allow_set_position =1;
							update_data_cmd =1;
							relay_state =STAIR_RELAY6_OFF; 
							higo_ap_.updateCommand(SET_RELAY6_STATE, count,0,relay_state);//38
						}
				    	break;	
									

			}
			command_switch_counts++;

		
			readBufferUpdate();

			cm.update(ros::Time::now(), ros::Duration(1 / controller_freq_));


			writeBufferUpdate();

			robot_state.motor3_speed =higo_ap_.getRobotAbstract()->ask_position_config.positionPhaseChange;
			robot_state.motor4_speed =higo_ap_.getRobotAbstract()->ask_expect_motor_speed.servo4;    
            robot_state.motor3_error_state=higo_ap_.getRobotAbstract()->motor_error_state.error3 ;
			robot_state.motor4_error_state=higo_ap_.getRobotAbstract()->motor_error_state.error4 ;

			robot_state_publisher_.publish(robot_state);
			
			// std::cerr <<(int)count<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
			currentTime = ros::Time::now();

			rate.sleep();

			count++;


		}

		cm_spinner.stop();
		hw_spinner.stop();

	}

