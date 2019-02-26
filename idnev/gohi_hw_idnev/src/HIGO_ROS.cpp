#include <gohi_hw/HIGO_ROS.h>




void HIGO_ROS::idcard_read_config_callback(const gohi_hw_idnev_msgs::idcard_read_config& msg)
 {
	std::cerr << "idcard is  " << std::endl;

	higo_ap_.getRobotAbstract()->id_info_data.id_number=msg.data[0];
	// higo_ap_.getRobotAbstract()->id_info_data.x_speed =msg.data[1];
	

	// higo_ap_.getRobotAbstract()->id_info_data.Rz=msg.data[2];

	// higo_ap_.getRobotAbstract()->rfid_read_data.singnal_intensity=msg.data[3];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_state=msg.data[4];
	// higo_ap_.getRobotAbstract()->rfid_read_data.write_state=msg.data[5];

	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data1=msg.data[6];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data2=msg.data[7];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data3=msg.data[8];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data4=msg.data[9];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data5=msg.data[10];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data6=msg.data[11];    
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data7=msg.data[12];
	// higo_ap_.getRobotAbstract()->rfid_read_data.read_from_reg_data8=msg.data[13];  


	// // higo_ap_.getRobotAbstract()->euler_angle.pitch=msg.data[14];
	// // higo_ap_.getRobotAbstract()->euler_angle.roll =msg.data[15];
	// // higo_ap_.getRobotAbstract()->euler_angle.yaw=msg.data[16];


	std::cerr <<"ID number =" <<msg.data[0]<<std::endl; 
	// std::cerr <<"x_speed   =" <<msg.data[1]<<std::endl;  
	// std::cerr <<"Rz        =" <<msg.data[2]<<std::endl; 


	// std::cerr <<"measure singnal " <<msg.data[5]<<std::endl;   
	// std::cerr <<"measure read_state  " <<msg.data[4]<<std::endl;   	
	// std::cerr <<"measure write_state  " <<msg.data[3]<<std::endl; 

	// std::cerr <<"ID1 interface   " <<msg.data[6]<<std::endl; 				  
	// std::cerr <<"ID2 interface   " <<msg.data[7]<<std::endl; 
	// // std::cerr <<"ID3 interface   " <<msg.data[8]<<std::endl; 
	// // std::cerr <<"ID4 interface   " <<msg.data[9]<<std::endl; 
	// // std::cerr <<"ID5 interface   " <<msg.data[10]<<std::endl; 
	// // std::cerr <<"ID6 interface   " <<msg.data[11]<<std::endl; 
	// // std::cerr <<"ID7 interface   " <<msg.data[12]<<std::endl; 								
	// // std::cerr <<"ID8 interface   " <<msg.data[13]<<std::endl; 		


  	// idcard_read_flag=1;
								  
 }




HIGO_ROS::HIGO_ROS(ros::NodeHandle &nh, std::string url, std::string config_addr,std::string idConfig_addr) :
		higo_ap_(url, config_addr,idConfig_addr),
		nh_(nh)
	{
		//get the parameter
		nh_.setCallbackQueue(&queue_);
        base_mode_ = "2diff-wheel";
		with_arm_ = false;
		controller_freq_ = 100;
		idcard_write_flag=0;
		nh_.getParam("base_mode", base_mode_);
		nh_.getParam("with_arm", with_arm_);
		nh_.getParam("freq", controller_freq_);

		idnev_state_publisher_  = nh_.advertise<gohi_hw_idnev_msgs::idnev_state>("/idnev_state_data", 1000);
		idnev_state_subscriber_ = nh_.subscribe("/idcard_read_config/cmd", 1,  &HIGO_ROS::idcard_read_config_callback, this);
       
		
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

		ros::NodeHandle cm_nh("hw_idnev");
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

	
			// higo_ap_.updateCommand(READ_EULER_ANGLE, count,0);//38
			if(higo_ap_.dataAnalysis(higo_ap_.getRobotAbstract()->id_info_data)){
				idnev_state_.id_number =higo_ap_.getRobotAbstract()->id_info_data.id_number;
				idnev_state_.x_speed =higo_ap_.getRobotAbstract()->id_info_data.x_speed;
				idnev_state_.Rz =higo_ap_.getRobotAbstract()->id_info_data.Rz;
				idnev_state_publisher_.publish(idnev_state_);			  
			}else{
				//do nothing 
			}
			// std::cerr <<"measure pitch  " <<robot->euler_angle.pitch*180.0/32768  <<std::endl;  
        // std::cerr <<"measure roll  " <<robot->euler_angle.roll *180.0/32768<<std::endl;   
        // std::cerr <<"measure yaw  " <<robot->euler_angle.yaw*180.0/32768<<std::endl;   

		    // imu_state_.euler_x=higo_ap_.getRobotAbstract()->euler_angle.pitch;
			// imu_state_.euler_y=higo_ap_.getRobotAbstract()->euler_angle.roll;				
			// imu_state_.euler_z=higo_ap_.getRobotAbstract()->euler_angle.yaw;					
			//----------------------------------------------------
			readBufferUpdate();

			cm.update(ros::Time::now(), ros::Duration(1 / controller_freq_));

			writeBufferUpdate();     
			 
			rate.sleep();
			

			count++;


			
			currentTime = ros::Time::now();
		}

		cm_spinner.stop();
		hw_spinner.stop();

	}

