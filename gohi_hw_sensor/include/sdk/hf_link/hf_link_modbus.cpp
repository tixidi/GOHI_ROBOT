#include "hf_link_modbus.h"
#include "stdio.h"
#include <string.h>
#include <iostream>


unsigned char HFLink_Modbus::byteAnalysisCall(const unsigned char rx_byte)
{
          
    if( receiveStates(rx_byte) )
    {
        //receive a new message
        unsigned char package_update = packageAnalysis();
        if(package_update == 1) {write_analysis_package_count++;        
        //std::cerr << "write Out" <<write_analysis_package_count<<std::endl;
        }
        return package_update;
    }
    return 0;
}

unsigned char HFLink_Modbus::byteAnalysisCall_R(const unsigned char rx_byte)
{

//    std::cerr <<"receive doing"  <<std::endl;//setup 
    if( receiveStates_R(rx_byte) )
    {
           
        // std::cerr <<"receive ok"  <<std::endl;//setup 
        //receive a new message
        unsigned char package_update = packageAnalysis();
        if(package_update == 1) {read_analysis_package_count++;
        // std::cerr << "read Out" <<read_analysis_package_count<<std::endl;
        }

        return package_update;
    }
    return 0;
}


/***********************************************************************************************************************
* Function:
*
* Scope:
*
* Description:
*
* Arguments:
*
* Return:
*
* Cpu_Time:    stm32f4+fpu(1 us)
*
* History:
***********************************************************************************************************************/
unsigned char HFLink_Modbus::packageAnalysis(void)
{
   unsigned char analysis_state;

   short int temp_laxian_length ; 
   short int temp_euler_angle[3] ; 

   short int temp_RFID_X_Y_SPEED;  //RFID数据//
   


    if(robot == NULL){
        printf(" error , the robot is NULL  \n");
        return 0;
    }


    // std::cerr <<"wwww1  csdafd " <<(int)rx_message.slave_addr<<std::endl;

    // if(rx_message.slave_addr==MOTOR1_ADDR)
    // {
    //     if(rx_message.slave_reg_addr==READ_ERROR_STATE_ADDR)                     command_state_=READ_MOT1_ERROR_STATE;        
    //     else if(rx_message.slave_reg_addr==READ_MOT_SPEED_ADDR)                  command_state_=READ_MOT1_SPEED;
    //     else if(rx_message.slave_reg_addr==READ_POSITION_COMPLETE_STATE_ADDR)    command_state_=READ_CAR1_MOTOR1_COMPLETE_STATE;
    //     else if(rx_message.slave_reg_addr==READ_MOT_POSITION_ADDR)               command_state_=READ_MOT1_REAL_POSITION;
    //     else if(rx_message.slave_reg_addr==SET_BRAKE_STATE_ADDR)                 command_state_=SET_MOT1_BRAKE_STATE;
    //     else if(rx_message.slave_reg_addr==SET_MOT_SPEED_ADDR)                   command_state_=SET_CAR1_LEFT_SPEED_CONTROL;
    //     else                                                                     command_state_=LAST_COMMAND_FLAG_;
    // }
    // else if(rx_message.slave_addr==MOTOR2_ADDR)
    // {
    //     if(rx_message.slave_reg_addr==READ_ERROR_STATE_ADDR)                     command_state_=READ_MOT2_ERROR_STATE;        
    //     else if(rx_message.slave_reg_addr==READ_MOT_SPEED_ADDR)                  command_state_=READ_MOT2_SPEED;       
    //     else if(rx_message.slave_reg_addr==READ_POSITION_COMPLETE_STATE_ADDR)    command_state_=READ_CAR1_MOTOR2_COMPLETE_STATE;
    //     else if(rx_message.slave_reg_addr==READ_MOT_POSITION_ADDR)               command_state_=READ_MOT2_REAL_POSITION; 
    //     else if(rx_message.slave_reg_addr==SET_BRAKE_STATE_ADDR)                 command_state_=SET_MOT2_BRAKE_STATE;
    //     else if(rx_message.slave_reg_addr==SET_MOT_SPEED_ADDR)                   command_state_=SET_CAR1_RIGHT_SPEED_CONTROL;
    //     else                                                                     command_state_=LAST_COMMAND_FLAG_;
    // }
    // else if(rx_message.slave_addr==MOTOR3_ADDR)
    // {
    //     if(rx_message.slave_reg_addr==READ_ERROR_STATE_ADDR)                     command_state_=READ_MOT3_ERROR_STATE;        
    //     else if(rx_message.slave_reg_addr==READ_MOT_SPEED_ADDR)                  command_state_=READ_MOT3_SPEED;
    //     else if(rx_message.slave_reg_addr==READ_POSITION_COMPLETE_STATE_ADDR)    command_state_=READ_CAR2_MOTOR3_COMPLETE_STATE;
    //     else if(rx_message.slave_reg_addr==READ_MOT_POSITION_ADDR)               command_state_=READ_MOT3_REAL_POSITION;         
    //     else if(rx_message.slave_reg_addr==SET_BRAKE_STATE_ADDR)                 command_state_=SET_MOT3_BRAKE_STATE;
    //     else if(rx_message.slave_reg_addr==SET_MOT_SPEED_ADDR)                   command_state_=SET_CAR2_POSITION_CONTROL;
    //     else                                                                     command_state_=LAST_COMMAND_FLAG_;
    // }
    // else if(rx_message.slave_addr==MOTOR4_ADDR)
    // {
    //     if(rx_message.slave_reg_addr==READ_ERROR_STATE_ADDR)                     command_state_=READ_MOT4_ERROR_STATE;        
    //     else if(rx_message.slave_reg_addr==READ_MOT_SPEED_ADDR)                  command_state_=READ_MOT4_SPEED;
    //     else if(rx_message.slave_reg_addr==READ_POSITION_COMPLETE_STATE_ADDR)    command_state_=READ_CAR2_MOTOR4_COMPLETE_STATE;
    //     else if(rx_message.slave_reg_addr==READ_MOT_POSITION_ADDR)               command_state_=READ_MOT4_REAL_POSITION;         
    //     else if(rx_message.slave_reg_addr==SET_BRAKE_STATE_ADDR)                 command_state_=SET_MOT4_BRAKE_STATE;
    //     else if(rx_message.slave_reg_addr==SET_MOT_SPEED_ADDR)                   command_state_=SET_CAR2_SPEED_CONTROL;
    //     else                                                                     command_state_=LAST_COMMAND_FLAG_;
    // }
    // else if(rx_message.slave_addr==MOTOR5_ADDR)
    // {
    //     if(rx_message.slave_reg_addr==READ_ERROR_STATE_ADDR)                     command_state_=READ_MOT5_ERROR_STATE;        
    //     else if(rx_message.slave_reg_addr==READ_MOT_SPEED_ADDR)                  command_state_=READ_MOT5_SPEED;
    //     else if(rx_message.slave_reg_addr==READ_POSITION_COMPLETE_STATE_ADDR)    command_state_=READ_CAR3_MOTOR5_COMPLETE_STATE;
    //     else if(rx_message.slave_reg_addr==READ_MOT_POSITION_ADDR)               command_state_=READ_MOT5_REAL_POSITION;         
    //     else if(rx_message.slave_reg_addr==SET_BRAKE_STATE_ADDR)                 command_state_=SET_MOT5_BRAKE_STATE;
    //     else if(rx_message.slave_reg_addr==SET_MOT_SPEED_ADDR)                   command_state_=SET_CAR3_LEFT_SPEED_CONTROL;
    //     else                                                                     command_state_=LAST_COMMAND_FLAG_;
    // }    

    // else if(rx_message.slave_addr==MOTOR6_ADDR)
    // {
    //     if(rx_message.slave_reg_addr==READ_ERROR_STATE_ADDR)                     command_state_=READ_MOT6_ERROR_STATE;        
    //     else if(rx_message.slave_reg_addr==READ_MOT_SPEED_ADDR)                  command_state_=READ_MOT6_SPEED;
    //     else if(rx_message.slave_reg_addr==READ_POSITION_COMPLETE_STATE_ADDR)    command_state_=READ_CAR3_MOTOR6_COMPLETE_STATE;
    //     else if(rx_message.slave_reg_addr==READ_MOT_POSITION_ADDR)               command_state_=READ_MOT6_REAL_POSITION;         
    //     else if(rx_message.slave_reg_addr==SET_BRAKE_STATE_ADDR)                 command_state_=SET_MOT6_BRAKE_STATE;
    //     else if(rx_message.slave_reg_addr==SET_MOT_SPEED_ADDR)                   command_state_=SET_CAR3_RIGHT_SPEED_CONTROL;
    //     else                                                                     command_state_=LAST_COMMAND_FLAG_;
    // }    
    //else 
    if(rx_message.slave_addr==LAXIAN_ADDR)
    {
        if(rx_message.slave_reg_addr==READ_LAXIAN_POSITION_ADDR)                 command_state_=READ_LAXIAN_POSITION;
    }
    else if(rx_message.slave_addr==IMU_ADDR)
    {      
    
        // if(rx_message.slave_reg_addr==READ_EULER_ANGLE_ADDR)                     command_state_=READ_EULER_ANGLE;
    }
    else if(rx_message.slave_addr==RFID_ADDR)
    {       
        //  std::cerr <<"xxx4"  <<std::endl;//setup 
        if(rx_message.slave_reg_addr==READ_RFID_REG_DATA_ADDR)                   command_state_=READ_RFID_REG_DATA;
    }

    else if(rx_message.slave_addr==THERMOMETER_ADDR)   //--------------------温度传感器
    {       
        if(rx_message.slave_reg_addr==READ_THERMOMETER_REG_DATA_ADDR)                   command_state_=READ_THERMOMETER_REG_DATA;
    }
   
    // else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_CAR1)
    // {       
    //     command_state_=READ_INTERFACE_CAR1_SPEED_CONTROL;

    // }
    // else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_CAR2)
    // {       

    //      command_state_=READ_INTERFACE_CAR2_SPEED_CONTROL;

    // }
    // else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_CAR3)
    // {       

    //      command_state_=READ_INTERFACE_CAR3_POSITION_CONTROL;

    // }
    // else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_CAR4)
    // {       
    //      command_state_=READ_INTERFACE_CAR4_SINGLE_SPEED_CONTROL;
    // }
    // else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_CAR1_ODOM)
    // {       
    //      command_state_=READ_INTERFACE_CAR1_ODOM_CONTROL;
    // }
    //     else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_ID)
    // {       
    //      command_state_=READ_INTERFACE_ID_CONTROL;
    // }
    //     else if(rx_message.slave_addr==PAD_INTERFACE_ADDR_LASER)
    // {       
    //      command_state_=READ_INTERFACE_LASER_CONTROL;
    // }


    //  =0;

    switch (command_state_)
    {
    // case READ_MOT1_ERROR_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_error_state.error1 , sizeof(robot->motor_error_state.error1));
    //     break;
    // case READ_MOT2_ERROR_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_error_state.error2 , sizeof(robot->motor_error_state.error2));
    //     break;
    // case READ_MOT3_ERROR_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_error_state.error3 , sizeof(robot->motor_error_state.error3));
    //     break;
    // case READ_MOT4_ERROR_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_error_state.error4 , sizeof(robot->motor_error_state.error4));
    //     break;
    // case READ_MOT5_ERROR_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_error_state.error5 , sizeof(robot->motor_error_state.error5));
    //     break;
    // case READ_MOT6_ERROR_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_error_state.error6 , sizeof(robot->motor_error_state.error6));
    //     break;

    // case READ_MOT1_SPEED :      
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&temp_mea_servo1_speed , sizeof(robot->ask_measure_motor_speed.servo1));
    //     robot->ask_measure_motor_speed.servo1=(float)temp_mea_servo1_speed;
    //     robot->ask_measure_motor_speed.servo1=robot->ask_measure_motor_speed.servo1/(8*18/0.1/20);
    //     robot->ask_measure_motor_speed.servo1=robot->ask_measure_motor_speed.servo1*2*3.14/60;    
    //     std::cerr <<"command1  " <<robot->ask_measure_motor_speed.servo1 <<std::endl;  //rad/s      
    //     robot->motor_pos_comp_state.posComp3=0;
    //     // std::cerr <<"wwww1" <<(int)robot->motor_pos_comp_state.posComp3<<std::endl;
    //     break;
    // case READ_MOT2_SPEED :      
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&temp_mea_servo2_speed , sizeof(robot->ask_measure_motor_speed.servo2));
    //     robot->ask_measure_motor_speed.servo2=(float)temp_mea_servo2_speed;
    //     robot->ask_measure_motor_speed.servo2=robot->ask_measure_motor_speed.servo2/(8*18/0.1/20);
    //     robot->ask_measure_motor_speed.servo2=robot->ask_measure_motor_speed.servo2*2*3.14/60;
    //     std::cerr <<"command2  "<<robot->ask_measure_motor_speed.servo2 <<std::endl;//rad/s
    //     robot->motor_pos_comp_state.posComp3=0;
    //     // std::cerr <<"wwww2" <<(int)robot->motor_pos_comp_state.posComp3<<std::endl;        
    //     break;
    // case READ_MOT3_SPEED :      
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo3 , sizeof(robot->ask_measure_motor_speed.servo3));
    //     break;
    // case READ_MOT4_SPEED :      
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo4 , sizeof(robot->ask_measure_motor_speed.servo4));
    //     break;
    // case READ_MOT5_SPEED :      
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo5 , sizeof(robot->ask_measure_motor_speed.servo5));
    //     break;
    // case READ_MOT6_SPEED :      
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo6 , sizeof(robot->ask_measure_motor_speed.servo6));
    //     break;


    // case READ_CAR1_MOTOR1_COMPLETE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_pos_comp_state.posComp1 , sizeof(robot->motor_pos_comp_state.posComp1));
    //     break;
    // case READ_CAR1_MOTOR2_COMPLETE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_pos_comp_state.posComp2 , sizeof(robot->motor_pos_comp_state.posComp2));
    //     break;
    // case READ_CAR2_MOTOR3_COMPLETE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->motor_pos_comp_state.posComp3 ,     sizeof(robot->motor_pos_comp_state.posComp3));
    //     // std::cerr <<"servo3 state  " <<(int)robot->motor_pos_comp_state.posComp3<<std::endl;
    //     break;
    // case READ_CAR2_MOTOR4_COMPLETE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_pos_comp_state.posComp4 , sizeof(robot->motor_pos_comp_state.posComp4));
    //     break;
    // case READ_CAR3_MOTOR5_COMPLETE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_pos_comp_state.posComp5 , sizeof(robot->motor_pos_comp_state.posComp5));
    //     break;
    // case READ_CAR3_MOTOR6_COMPLETE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->motor_pos_comp_state.posComp6 , sizeof(robot->motor_pos_comp_state.posComp6));
    //     break;


    // case READ_MOT1_REAL_POSITION:
    //     // d_past_angle[0] =0;          
    //     analysis_state=readCommandAnalysis(command_state_ , (int* )&temp_mea_motor1_position , sizeof(robot->ask_measure_motor_position.position1));
    //     robot->ask_measure_motor_position.position1=(float)temp_mea_motor1_position;
  
    //     robot->ask_measure_motor_position_dif.position1=robot->ask_measure_motor_position.position1-robot->ask_measure_motor_position_last.position1;
    //     robot->ask_measure_motor_position_last.position1=robot->ask_measure_motor_position.position1;
    //     //recording total angle for robot coordinate calculation
    //     d_past_angle[0] = (robot->ask_measure_motor_position_dif.position1/per_circle_position)*360;
    //     past_total_angle[0]+= ( robot->ask_measure_motor_position_dif.position1/per_circle_position)*360;

    //     //calc motor speed  degree/s
    //     robot->ask_measure_motor_speed.servo1=   robot->ask_measure_motor_position_dif.position1 * 360 / ( per_circle_position*pid_t )*degree_to_radian;

    //     std::cerr <<"command 3__________" <<(int)robot->motor_pos_comp_state.posComp3<<std::endl;
    //     break;
    // case READ_MOT2_REAL_POSITION :  
    //     // d_past_angle[1] =0;            
    //     analysis_state=readCommandAnalysis(command_state_ , (int* )&temp_mea_motor2_position , sizeof(robot->ask_measure_motor_position.position2));
    //     robot->ask_measure_motor_position.position2=(float)temp_mea_motor2_position;

    //     robot->ask_measure_motor_position_dif.position2=robot->ask_measure_motor_position.position2-robot->ask_measure_motor_position_last.position2;
    //     robot->ask_measure_motor_position_last.position2=robot->ask_measure_motor_position.position2;
    //     //recording total angle for robot coordinate calculation
    //     d_past_angle[1] = (robot->ask_measure_motor_position_dif.position2/per_circle_position)*360;
    //     past_total_angle[1]+= ( robot->ask_measure_motor_position_dif.position2/per_circle_position)*360;

    //     //calc motor speed  degree/s
    //     robot->ask_measure_motor_speed.servo2=   robot->ask_measure_motor_position_dif.position2 * 360 / ( per_circle_position*pid_t )*degree_to_radian;

    //     std::cerr <<"command 4----------" <<(int)robot->motor_pos_comp_state.posComp3<<std::endl;        
    //     break;
        
    // case READ_MOT3_REAL_POSITION :      
    //     // analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo3 , sizeof(robot->ask_measure_motor_speed.servo3));
    //     break;
    // case READ_MOT4_REAL_POSITION :      
    //     // analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo4 , sizeof(robot->ask_measure_motor_speed.servo4));
    //     break;
    // case READ_MOT5_REAL_POSITION :      
    //     // analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo5 , sizeof(robot->ask_measure_motor_speed.servo5));
    //     break;
    // case READ_MOT6_REAL_POSITION :      
    //     // analysis_state=readCommandAnalysis(command_state_ , (short int* )&robot->ask_measure_motor_speed.servo5 , sizeof(robot->ask_measure_motor_speed.servo5));
    //     break;

    // case SET_MOT1_BRAKE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->ask_brake_config.brake1 , sizeof(robot->ask_brake_config.brake1));
    //     break;   
    // case SET_MOT2_BRAKE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->ask_brake_config.brake2 , sizeof(robot->ask_brake_config.brake2));
    //     break;  
    // case SET_MOT3_BRAKE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->ask_brake_config.brake3 , sizeof(robot->ask_brake_config.brake3));
    //     break;   
    // case SET_MOT4_BRAKE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->ask_brake_config.brake4 , sizeof(robot->ask_brake_config.brake4));
    //     break;  
    // case SET_MOT5_BRAKE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->ask_brake_config.brake5 , sizeof(robot->ask_brake_config.brake5));
    //     break;        
    // case SET_MOT6_BRAKE_STATE :
    //     analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&robot->ask_brake_config.brake6 , sizeof(robot->ask_brake_config.brake6));
    //     break;      


    // case SET_CAR1_LEFT_SPEED_CONTROL :
    //     analysis_state=setCommandAnalysis(command_state_ , (float* )&robot->ask_expect_motor_speed.servo1 , sizeof(robot->ask_expect_motor_speed.servo1) );
    //     break;
    // case SET_CAR1_RIGHT_SPEED_CONTROL :
    //     analysis_state=setCommandAnalysis(command_state_ , (float* )&robot->ask_expect_motor_speed.servo2 , sizeof(robot->ask_expect_motor_speed.servo2) );
    //     break;        
    // case SET_CAR2_POSITION_CONTROL :
    //     analysis_state=setCommandAnalysis(command_state_ , (float* )&robot->ask_expect_motor_speed.servo3 , sizeof(robot->ask_expect_motor_speed.servo3) );
    //     break;   
    // case SET_CAR2_SPEED_CONTROL :
    //     analysis_state=setCommandAnalysis(command_state_ , (float* )&robot->ask_expect_motor_speed.servo4 , sizeof(robot->ask_expect_motor_speed.servo4) );
    //     break;
    // case SET_CAR3_LEFT_SPEED_CONTROL :
    //     analysis_state=setCommandAnalysis(command_state_ , (float* )&robot->ask_expect_motor_speed.servo5 , sizeof(robot->ask_expect_motor_speed.servo5) );
    //     break;
    // case SET_CAR3_RIGHT_SPEED_CONTROL :
    //     analysis_state=setCommandAnalysis(command_state_ , (float* )&robot->ask_expect_motor_speed.servo6 , sizeof(robot->ask_expect_motor_speed.servo6) );
    //     break;
    //---------------------------------------------------------------------------------------------------------------------------------
 

    case READ_LAXIAN_POSITION:
        analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&temp_laxian_length , sizeof(robot->laxian_length.length_data) );   
        robot->laxian_length.length_data=temp_laxian_length;
        std::cerr <<"拉线传感器数据：******************************  " <<std::endl; 
        std::cerr <<"measure Length: " <<temp_laxian_length<<"  mm" <<std::endl; 
        break;
    case READ_EULER_ANGLE:
        std::cerr <<"惯导数据：******************************  " <<std::endl; 
        std::cerr <<"yyy2"  <<std::endl;//setup 
        analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->euler_angle , sizeof(robot->euler_angle) );   
        std::cerr <<"measure pitch  " <<robot->euler_angle.pitch*180.0/32768  <<std::endl;  
        std::cerr <<"measure roll  " <<robot->euler_angle.roll *180.0/32768<<std::endl;   
        std::cerr <<"measure yaw  " <<robot->euler_angle.yaw*180.0/32768<<std::endl;   
        break;

    case READ_RFID_REG_DATA:
  
       // analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&temp_RFID_X_Y_SPEED , sizeof(robot->RFIDData. x_y_speed) ); 
        analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->rfid_read_data , sizeof(robot->rfid_read_data ));   
        std::cerr <<"射频卡数据：******************************  " <<std::endl; 
        std::cerr <<"write_state  " <<(short int)robot->rfid_read_data.write_state<<std::endl; 
        std::cerr <<"read_state  " <<(short int)robot->rfid_read_data.read_state<<std::endl; 
        std::cerr <<"singnal_intensity  " <<(short int)robot->rfid_read_data.singnal_intensity<<std::endl; 

        std::cerr <<"read_from_reg_data1  " <<(short int)robot->rfid_read_data.read_from_reg_data1<<std::endl; 
        std::cerr <<"read_from_reg_data2  " <<(short int)robot->rfid_read_data.read_from_reg_data2<<std::endl; 
        std::cerr <<"read_from_reg_data3  " <<(short int)robot->rfid_read_data.read_from_reg_data3<<std::endl; 
        std::cerr <<"read_from_reg_data4  " <<(short int)robot->rfid_read_data.read_from_reg_data4<<std::endl; 
        std::cerr <<"read_from_reg_data5  " <<(short int)robot->rfid_read_data.read_from_reg_data5<<std::endl; 
        std::cerr <<"read_from_reg_data6  " <<(short int)robot->rfid_read_data.read_from_reg_data6<<std::endl; 
        std::cerr <<"read_from_reg_data7  " <<(short int)robot->rfid_read_data.read_from_reg_data7<<std::endl; 
        std::cerr <<"read_from_reg_data8  " <<(short int)robot->rfid_read_data.read_from_reg_data8<<std::endl; 

        break;

     case READ_THERMOMETER_REG_DATA://读温度传感器
 
        analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->Temperature_Data , sizeof(robot->Temperature_Data ));   
        // std::cerr <<"温度传感器1路  " <<(short int)robot->Temperature_Data.read_from_reg_data1/10<<" 摄氏度 "std::endl; 
        // std::cerr <<"温度传感器2路  " <<(short int)robot->Temperature_Data.read_from_reg_data2/10<<"摄氏度  "std::endl; 
         std::cerr <<"温度数据：******************************  " <<std::endl; 
         std::cerr <<"温度传感器3路: " <<(float)robot->Temperature_Data.read_from_reg_data3/10<<" 摄氏度  "<<std::endl; 
         std::cerr <<"温度传感器4路: " <<(float)robot->Temperature_Data.read_from_reg_data4/10<<" 摄氏度  "<<std::endl; 

        break;
    // case READ_INTERFACE_CAR1_SPEED_CONTROL:
    //     //    std::cerr <<"command8_____" <<robot->ask_expect_motor_speed.servo1 <<std::endl;//setup 
    //     analysis_state=readCommandAnalysis(command_state_ ,(short int*)&robot->car1_speed_config , sizeof(robot->car1_speed_config ) );   
    //     robot->receive_package_flag=1;
      
    //     std::cerr <<"car1 interface x_speed  " <<(float)robot->car1_speed_config.x_speed/100.0<<std::endl; 
    //     std::cerr <<"car1 interface y_speed  " <<(float)robot->car1_speed_config.y_speed/100.0<<std::endl; 
    //     std::cerr <<"car1 interface z_speed  " <<(float)robot->car1_speed_config.z_speed/100.0<<std::endl; 

    //     break;
       
    // case READ_INTERFACE_CAR2_SPEED_CONTROL:
    //     analysis_state=readCommandAnalysis(command_state_ ,(short int*)&robot->car1_speed_config , sizeof(robot->car1_speed_config ));   
    //     robot->receive_package_flag=2;
    //     std::cerr <<"car2 interface x_speed  " <<(float)robot->car1_speed_config.x_speed/100.0<<std::endl; 
    //     std::cerr <<"car2 interface y_speed  " <<(float)robot->car1_speed_config.y_speed/100.0<<std::endl; 
    //     std::cerr <<"car2 interface z_speed  " <<(float)robot->car1_speed_config.z_speed/100.0<<std::endl; 
    //     break;

    // case READ_INTERFACE_CAR3_POSITION_CONTROL:
    //     analysis_state=readCommandAnalysis(command_state_ ,(short int*)&robot->car3_position_config , sizeof(robot->car3_position_config ) );   
    //     robot->receive_package_flag=3;
    //     std::cerr <<"car3 interface speed  " <<(float)robot->car3_position_config.speed/100.0<<std::endl; 
    //     std::cerr <<"car3 interface type  " <<(short int)robot->car3_position_config.type<<std::endl; 
    //     std::cerr <<"car3 interface position  " <<(short int)robot->car3_position_config.position<<std::endl; 
 
    //     break;       
    
    // case READ_INTERFACE_CAR4_SINGLE_SPEED_CONTROL:
    //     analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->car4_single_speed_config , sizeof(robot->car4_single_speed_config ) );   
    //     robot->receive_package_flag=4;
    //     // std::cerr <<"car4 interface m1_speed  " <<(float)robot->car4_single_speed_config.m1_speed/100.0<<std::endl; 
    //     // std::cerr <<"car4 interface m2_speed  " <<(float)robot->car4_single_speed_config.m2_speed/100.0<<std::endl; 
    //     // std::cerr <<"car4 interface m3_speed  " <<(float)robot->car4_single_speed_config.m3_speed/100.0<<std::endl;  
    //     break;
    // case READ_INTERFACE_CAR1_ODOM_CONTROL:
    //     analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->car_global_position_config, sizeof(robot->car_global_position_config ) );   
    //     robot->receive_package_flag=5;
    //     std::cerr <<"car1 X Position  " <<(float)robot->car_global_position_config.position_X/100.0<<std::endl; 
    //     std::cerr <<"car1 Y Position  " <<(float)robot->car_global_position_config.position_Y/100.0<<std::endl; 
    //     std::cerr <<"car1 Z Position  " <<(float)robot->car_global_position_config.position_Z/100.0<<std::endl;  
    //     break;
    // case READ_INTERFACE_ID_CONTROL: 
    //     analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->rfid_write_data , sizeof(robot->rfid_write_data ) );   
    //     robot->receive_package_flag=6;
 

    //     break;
    // case READ_INTERFACE_LASER_CONTROL:
    //     analysis_state=readCommandAnalysis(command_state_ , (short int*)&robot->laser_range_config , sizeof(robot->laser_range_config ) );   
    //     robot->receive_package_flag=7;
    //     std::cerr <<"Laser range L  " <<(short int)robot->laser_range_config.laser_range_L<<std::endl; 
    //     std::cerr <<"Laser range R  " <<(short int)robot->laser_range_config.laser_range_R<<std::endl; 
    //     robot->laser_scan_range=robot->laser_range_config.laser_range_R-robot->laser_range_config.laser_range_L;
    //     if(robot->laser_scan_num>0)  
    //     {
    //         robot->laser_scan_num=(unsigned short int)robot->laser_scan_range/robot->laser_scan_resolution;
                    
    //         memcpy(tx_to_PAD_buffer,robot->laser_scan_data,robot->laser_scan_num);    
    //         tx_to_PAD_num=robot->laser_scan_num;
    //         std::cerr <<"Laser scan num  " <<robot->laser_scan_num<<std::endl; 
    //     }
    //     break;                

    default :
        analysis_state = 0;
        break;

    }

    // rx_message.slave_addr=0;    //clear flag
    // rx_message.command_id=0;
    // rx_message.slave_reg_addr=0;
    // memset(&rx_message.data , 0 , sizeof(rx_message.data));


    // tx_message.slave_addr=0;    //clear flag
    // tx_message.command_id=0;
    // tx_message.slave_reg_addr=0;
    // memset(&tx_message.data , 0 , sizeof(tx_message.data));


    return analysis_state;
}

/***********************************************************************************************************************
* Function:    void HFLink::masterSendCommand(Command command)
*
* Scope:       public
*
* Description: send a command or data to the friend_id
*              this function is olny belongs to master
*
*
* Arguments:
*
* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/

unsigned char HFLink_Modbus::masterSendCommand(const MotorModbusCommand command_state)
{
  
   
   void *single_command;
   short int v_speed = 1 ;//(m/s)
   float  per_circle_position1 =(360/120)*8*18;

    receive_package_renew[(unsigned char)command_state] = 0 ;

    
    switch (command_state)
    {
    // case READ_MOT1_ERROR_STATE :
    //     sendStruct(MOTOR1_ADDR , READ_REG,READ_ERROR_STATE_ADDR,(unsigned char *)single_command , 0);
    //     break;
    // case READ_MOT2_ERROR_STATE :
    //     sendStruct(MOTOR2_ADDR , READ_REG,READ_ERROR_STATE_ADDR,(unsigned char *)single_command , 0);
    //     break;    
    // case READ_MOT3_ERROR_STATE :
    //     sendStruct(MOTOR3_ADDR , READ_REG,READ_ERROR_STATE_ADDR,(unsigned char *)single_command , 0 );
    //     break;                         
    // case READ_MOT4_ERROR_STATE :
    //     sendStruct(MOTOR4_ADDR , READ_REG,READ_ERROR_STATE_ADDR,(unsigned char *)single_command , 0 );
    //     break;
    // case READ_MOT5_ERROR_STATE :
    //     sendStruct(MOTOR5_ADDR , READ_REG,READ_ERROR_STATE_ADDR,(unsigned char *)single_command , 0 );
    //     break;    
    // case READ_MOT6_ERROR_STATE :
    //     sendStruct(MOTOR6_ADDR , READ_REG,READ_ERROR_STATE_ADDR,(unsigned char *)single_command , 0 );
    //     break;         

    // case READ_MOT1_SPEED :
    //     sendStruct(MOTOR1_ADDR , READ_REG,READ_MOT_SPEED_ADDR,(unsigned char *)single_command , 0);
    //     break;
    // case READ_MOT2_SPEED :
    //     sendStruct(MOTOR2_ADDR , READ_REG,READ_MOT_SPEED_ADDR,(unsigned char *)single_command , 0);
    //     break;
    // case READ_MOT3_SPEED :
    //     sendStruct(MOTOR3_ADDR , READ_REG,READ_MOT_SPEED_ADDR,(unsigned char *)single_command , 0);
    //     break;
    // case READ_MOT4_SPEED :
    //     sendStruct(MOTOR4_ADDR , READ_REG,READ_MOT_SPEED_ADDR,(unsigned char *)single_command , 0);
    //     break;
    // case READ_MOT5_SPEED :
    //     sendStruct(MOTOR5_ADDR , READ_REG,READ_MOT_SPEED_ADDR,(unsigned char *)single_command , 0);
    //     break;
    // case READ_MOT6_SPEED :
    //     sendStruct(MOTOR6_xingsong_parametersommand , 0);
    //     break;

//     case READ_MOT1_REAL_POSITION :
//         sendStruct(MOTOR1_ADDR , READ_REG,READ_MOT_POSITION_ADDR,(unsigned char *)single_command , 0);
//         break;
//     case READ_MOT2_REAL_POSITION :
//         sendStruct(MOTOR2_ADDR , READ_REG,READ_MOT_POSITION_ADDR,(unsigned char *)single_command , 0);
//         break;
//     case READ_MOT3_REAL_POSITION :
//         sendStruct(MOTOR3_ADDR , READ_REG,READ_MOT_POSITION_ADDR,(unsigned char *)single_command , 0);
//         break;
//     case READ_MOT4_REAL_POSITION :
//         sendStruct(MOTOR4_ADDR , READ_REG,READ_MOT_POSITION_ADDR,(unsigned char *)single_command , 0);
//         break;
//     case READ_MOT5_REAL_POSITION :
//         sendStruct(MOTOR5_ADDR , READ_REG,READ_MOT_POSITION_ADDR,(unsigned char *)single_command , 0);
//         break;
//     case READ_MOT6_REAL_POSITION :
//         sendStruct(MOTOR6_ADDR , READ_REG,READ_MOT_POSITION_ADDR,(unsigned char *)single_command , 0);
//         break;

//     case READ_CAR1_MOTOR1_COMPLETE_STATE :
//         sendStruct(MOTOR1_ADDR , READ_REG,READ_POSITION_COMPLETE_STATE_ADDR,(unsigned char *)single_command , 0);              
//         break;
//     case READ_CAR1_MOTOR2_COMPLETE_STATE :
//         sendStruct(MOTOR2_ADDR , READ_REG,READ_POSITION_COMPLETE_STATE_ADDR,(unsigned char *)single_command , 0);              
//         break;
//     case READ_CAR2_MOTOR3_COMPLETE_STATE :
//         sendStruct(MOTOR3_ADDR , READ_REG,READ_POSITION_COMPLETE_STATE_ADDR,(unsigned char *)single_command , 0);              
//         break;        
//     case READ_CAR2_MOTOR4_COMPLETE_STATE :
//         sendStruct(MOTOR4_ADDR , READ_REG,READ_POSITION_COMPLETE_STATE_ADDR,(unsigned char *)single_command , 0);              
//         break;
//     case READ_CAR3_MOTOR5_COMPLETE_STATE :
//         sendStruct(MOTOR5_ADDR , READ_REG,READ_POSITION_COMPLETE_STATE_ADDR,(unsigned char *)single_command , 0);              
//         break;
//     case READ_CAR3_MOTOR6_COMPLETE_STATE :
//         sendStruct(MOTOR6_ADDR , READ_REG,READ_POSITION_COMPLETE_STATE_ADDR,(unsigned char *)single_command , 0);              
//         break;

//     case SET_MOT1_BRAKE_STATE :
//         sendStruct(MOTOR1_ADDR , WRITE_REG,SET_BRAKE_STATE_ADDR, (unsigned char *)&robot->ask_brake_config.brake1 , sizeof(robot->ask_brake_config.brake1));  
//         break;
//     case SET_MOT2_BRAKE_STATE :
//         sendStruct(MOTOR2_ADDR , WRITE_REG,SET_BRAKE_STATE_ADDR, (unsigned char *)&robot->ask_brake_config.brake2 , sizeof(robot->ask_brake_config.brake2));     
//         break;
//     case SET_MOT3_BRAKE_STATE :
//         sendStruct(MOTOR3_ADDR , WRITE_REG,SET_BRAKE_STATE_ADDR, (unsigned char *)&robot->ask_brake_config.brake3 , sizeof(robot->ask_brake_config.brake3) );  
//         break;
//     case SET_MOT4_BRAKE_STATE :
//         sendStruct(MOTOR4_ADDR , WRITE_REG,SET_BRAKE_STATE_ADDR, (unsigned char *)&robot->ask_brake_config.brake4 , sizeof(robot->ask_brake_config.brake4) );     
//         break;        
//     case SET_MOT5_BRAKE_STATE :
//         sendStruct(MOTOR5_ADDR , WRITE_REG,SET_BRAKE_STATE_ADDR, (unsigned char *)&robot->ask_brake_config.brake5 , sizeof(robot->ask_brake_config.brake5));        
//         break;        
//     case SET_MOT6_BRAKE_STATE :
//         sendStruct(MOTOR6_ADDR , WRITE_REG,SET_BRAKE_STATE_ADDR, (unsigned char *)&robot->ask_brake_config.brake6 , sizeof(robot->ask_brake_config.brake6));        
//         break;       


//     case SET_CAR1_LEFT_SPEED_CONTROL :

//         // robot->ask_expect_motor_speed.servo1=1.24;//setup  //rad/s
//         // std::cerr <<"command5_____" <<robot->ask_expect_motor_speed.servo1 <<std::endl;//setup 
//         robot->ask_expect_motor_speed.servo1=(robot->ask_expect_motor_speed.servo1)*60/2/3.14; //rpm
//         robot->ask_expect_motor_speed.servo1=robot->ask_expect_motor_speed.servo1*8*30/0.1/20;  

//         temp_ask_servo1_speed     =(short int )robot->ask_expect_motor_speed.servo1;
//         sendStruct(MOTOR1_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR, (unsigned char *)&temp_ask_servo1_speed, sizeof(temp_ask_servo1_speed) );      
//         break;
//     case SET_CAR1_RIGHT_SPEED_CONTROL :
//  //
//         // robot->ask_expect_motor_speed.servo2=-1.24;//31 rad/s
//         std::cerr <<"command6______" <<robot->ask_expect_motor_speed.servo2 <<std::endl;
//         robot->ask_expect_motor_speed.servo2=(robot->ask_expect_motor_speed.servo2)*60/2/3.14;
//         robot->ask_expect_motor_speed.servo2=robot->ask_expect_motor_speed.servo2*8*30/0.1/20;
//         temp_ask_servo2_speed     =(short int )robot->ask_expect_motor_speed.servo2;        
//         sendStruct(MOTOR2_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR, (unsigned char *)&temp_ask_servo2_speed, sizeof(temp_ask_servo2_speed) );
//         break;          
//     // case SET_CAR1_SPEED_CONTROL :
//     //     control_quality += 30;
        
//     //     sendStruct(MOTOR1_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR,(float* )&robot->ask_expect_motor_speed.servo1 , sizeof(robot->ask_expect_motor_speed.servo1) );
//     //     sendStruct(MOTOR2_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR,(float* )&robot->ask_expect_motor_speed.servo2 , sizeof(robot->ask_expect_motor_speed.servo2) );
//     //     break;
//     case SET_CAR2_POSITION_CONTROL :
//         // robot->ask_position_set.servo1=(short int)robot->expect_head_state.pitch;
//         robot->ask_position_set.servo1=   5.76;  //rad/s
//         robot->ask_position_set.position= 10  ;//rad
        
//         robot->ask_position_set.positiontype=1;

//         std::cerr <<"ask  position_config servo1" <<robot->ask_position_set.servo1 <<std::endl;
//         robot->ask_position_set.servo1=(robot->ask_position_set.servo1)*60/2/3.14;
//         robot->ask_position_set.servo1=robot->ask_position_set.servo1*8*18/0.1/20;
//         robot->ask_position_config.positionPhaseChange      =(short int )robot->ask_position_set.servo1;  
//         robot->ask_position_config.positiontype             =(short int )robot->ask_position_set.positiontype;  



//         robot->ask_position_set.position=(robot->ask_position_set.position*radian_to_degree*per_circle_position1)/360;
//         robot->ask_position_config.positionH=robot->ask_position_set.position>>16;   
//         robot->ask_position_config.positionL=(short int)(robot->ask_position_set.position&0xFFFF);   
        

//         // robot->ask_position_config.positionH=0;                                             //测试
//         // robot->ask_position_config.positionL=(short int)robot->expect_head_state.yaw&0xFF;  //测试
        

//         std::cerr <<"ask  position PhaseChange" <<robot->ask_position_config.positionPhaseChange <<std::endl;
//         std::cerr <<"ask  position positiontype" <<robot->ask_position_config.positiontype <<std::endl;

//         // std::cerr <<"ask  position position" <<robot->ask_position_set.positionDR,(unsigned char *)&robot->XS_ABMotor_Control, sizeof(robot->XS_ABMotor_Control)); 

//         // std::cerr <<"ask  position positionH" <<robot->ask_position_config.posiDR,(unsigned char *)&robot->XS_ABMotor_Control, sizeof(robot->XS_ABMotor_Control)); 
//         // break; tionH <<std::endl;
//         // std::cerr <<"ask  position positionL" <<robot->ask_position_config.posiDR,(unsigned char *)&robot->XS_ABMotor_Control, sizeof(robot->XS_ABMotor_Control)); 
//         // break; tionL <<std::endl;

//         sendStruct(MOTOR3_ADDR , WRITE_MORE_REG,SET_MOT_POSITION_ADDR,(unsigned char* )&robot->ask_position_config , sizeof(robot->ask_position_config) );
//         break;   
//     case SET_CAR2_SPEED_CONTROL :

//         // // robot->ask_expect_motor_speed.servo1=1.24;//setup  //rad/s
//         // std::cerr <<"xxx1" <<robot->ask_expect_motor_speed.servo1 <<std::endl;//setup 
//         // robot->ask_expect_motor_speed.servo1=(robot->ask_expect_motor_speed.servo1)*60/2/3.14; //rpm
//         // robot->ask_expect_motor_speed.servo1=robot->ask_expect_motor_speed.servo1*8*18/0.1/20;  

//         // temp_ask_servo1_speed     =(short int )robot->ask_expect_motor_speed.servo1;
//         sendStruct(MOTOR4_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR,(unsigned char *)&temp_ask_servo4_speed, sizeof(temp_ask_servo4_speed) );      
//         break;

//     case SET_CAR3_LEFT_SPEED_CONTROL:
//         sendStruct(MOTOR5_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR,(unsigned char *)&temp_ask_servo5_speed, sizeof(temp_ask_servo5_speed)  );
//         break;   
//     case SET_CAR3_RIGHT_SPEED_CONTROL :
//         sendStruct(MOTOR6_ADDR , WRITE_REG,SET_MOT_SPEED_ADDR,(unsigned char *)&temp_ask_servo6_speed, sizeof(temp_ask_servo6_speed)  );
//         break;


// /*兴颂驱动器AB电机控制*/
//     case SET_CAR5_SPEED_CONTROL :  
//          //robot->XS_ABMotor_Control.MotorA_State=0x0001; 
//          robot->XS_ABMotor_Control.MotorA_State=0x0001;
//          robot->XS_ABMotor_Control.MotorB_State=0x0001; 
//          robot->XS_ABMotor_Control.MotorA_Dir=0x0000; 
//          robot->XS_ABMotor_Control.MotorB_Dir=0x0000; 
//          robot->XS_ABMotor_Control.MotorA_rpmValue=0x07D0; 
//          robot->XS_ABMotor_Control.MotorB_rpmValue=0x07D0; 

//         sendStruct(MOTOR5_ADDR , WRITE_MORE_REG,SET_CAR5_SPEED_ADDR,(unsigned char *)&robot->XS_ABMotor_Control, sizeof(robot->XS_ABMotor_Control)); 
//         break; 

    case READ_LAXIAN_POSITION:
        sendStruct(LAXIAN_ADDR , READ_REG,READ_LAXIAN_POSITION_ADDR,(unsigned char *)single_command , 0);           
        break;             
    case READ_EULER_ANGLE:
        sendStruct(IMU_ADDR , READ_REG,READ_EULER_ANGLE_ADDR,(unsigned char *)single_command , 0);           
        break;

    case READ_RFID_REG_DATA:
        sendStruct(RFID_ADDR , READ_INPUT_REG,READ_RFID_REG_DATA_ADDR,(unsigned char *)single_command , 0);           
        break;    

    case SET_RFID_REG_DATA:  

        sendStruct(RFID_ADDR , WRITE_MORE_REG,SET_RFID_REG_DATA_ADDR,(unsigned char* )&robot->rfid_write_data , sizeof(robot->rfid_write_data));           
        break;   

    case READ_THERMOMETER_REG_DATA:  //读温度传感器

        sendStruct(THERMOMETER_ADDR , READ_REG,READ_THERMOMETER_REG_DATA_ADDR,(unsigned char *)single_command , 0);           
        break;      

    // case READ_INTERFACE_CAR1_SPEED_CONTROL:
    //     sendStructToPAD(PAD_INTERFACE_ADDR_CAR1 , READ_INPUT_REG,READ_INTERFACE_CAR1_SPEED_CONTROL_ADDR,(unsigned char *)single_command , 0);           
    //     break;    
    // case READ_INTERFACE_CAR2_SPEED_CONTROL:
    //     sendStructToPAD(PAD_INTERFACE_ADDR_CAR2 , READ_INPUT_REG,READ_INTERFACE_CAR2_SPEED_CONTROL_ADDR,(unsigned char *)single_command , 0);           
    //     break;    
    // case READ_INTERFACE_CAR3_POSITION_CONTROL:
    //     sendStructToPAD(PAD_INTERFACE_ADDR_CAR3 , READ_INPUT_REG,READ_INTERFACE_CAR3_POSITION_CONTROL_ADDR,(unsigned char *)single_command , 0);           
    //     break;    
    // case READ_INTERFACE_CAR4_SINGLE_SPEED_CONTROL:
    //     sendStructToPAD(PAD_INTERFACE_ADDR_CAR4 , READ_INPUT_REG,READ_INTERFACE_CAR4_SINGLE_SPEED_CONTROL_ADDR,(unsigned char *)single_command , 0);           
    //     break;    
    // case WRITE_SENSOR_DATA_TO_PAD_INTERFACE:
    //     sendStructToPAD(SENSOR_DATA_TO_PAD_INTERFACE , WRITE_MORE_REG,WRITE_SENSOR_DATA_TO_PAD_INTERFACE_ADDR,(unsigned char *)single_command , 0);      
     
    //     break;
    // case WRITE_LASER_DATA_TO_PAD_INTERFACE:
    //     sendStructToPAD(LASER_DATA_TO_PAD_INTERFACE , WRITE_MORE_REG,WRITE_LASER_DATA_TO_PAD_INTERFACE_ADDR,(unsigned char *)single_command , 0);               
    //     break;
        


   default : // case SET_CAR5_SPEED_CONTROL :  

        break;
    } 
    return 1;
}
/***********************************************************************************************************************
*Request16
*Request16
*Request16
*Request16
* Description:
*
* Arguments:
*
* Return:Request16
*

***************************************************************** ******************************************************/
unsigned char HFLink_Modbus::readCommandAnalysis(const MotorModbusCommand  command_state , unsigned char* p ,  unsigned short int len)
{
    if (hf_link_node_model == 1)
    { 
        memcpy(p , &rx_message.data[2] , len);
        receive_package_renew[(unsigned char)command_state] = 1 ;
    }

    return 1;
}
unsigned char HFLink_Modbus::readCommandAnalysis(const MotorModbusCommand command_state ,short int* p ,  unsigned short int len)
{
    if (hf_link_node_model == 1)
    {
        memcpy(p , &rx_message.data[0] , len);     

        receive_package_renew[(unsigned char)command_state] = 1 ;
    }

    return 1;
}
unsigned char HFLink_Modbus::readCommandAnalysis(const MotorModbusCommand command_state , int* p ,  unsigned short int len)
{
    if (hf_link_node_model == 1)
    { 
        memcpy(p , &rx_message.data[0] , len);     

        receive_package_renew[(unsigned char)command_state] = 1 ;
    }

    return 1;
}

unsigned char HFLink_Modbus::setCommandAnalysis(const MotorModbusCommand command_state , unsigned char* p ,  unsigned short int len)
{ 
    if (hf_link_node_model == 1) 
    { 
        printf("I'm master , received a ack ");
        receive_package_renew[(unsigned char)command_state] = 1 ;
    }
    
    return 1;
}
unsigned char HFLink_Modbus::setCommandAnalysis(const MotorModbusCommand command_state , float* p ,  unsigned short int len)
{

    if (hf_link_node_model == 1)
    { 
        printf("I'm master , received a ack ");
        receive_package_renew[(unsigned char)command_state] = 1 ;
    }
    
    return 1;
}
/***********************************************************************************************************************
* Function:    void HFLink::sendStruct(const Command command_state , unsigned char* p , const unsigned short int len)
*
* Scope:       private
*
* Description:
* len =0       send a Single command to the friend
*              if i am slave , it can be  feed back a ack to master or request instructions  like SHAKING_HANDS
*              if i am master , it can be s             ome request instructions like READ_ROBOT_SYSTEM_INFO READ_xxx
*
*
* len>0 :      send a Struct command to      // robot->expect_robot_speed.x=0.1;READ_RFID_REG_DATA

* Return:
*
* Cpu_Time:
*
* History:
***********************************************************************************************************************/

void HFLink_Modbus::sendStruct(const ModbusSlaveAddr slave_addr,const ModbusCommandCode command_Code, const ModbusCommandRegAddr command_reg_addr , unsigned char* p ,  unsigned short int len)
{
    tx_message.slave_addr =  (unsigned char)slave_addr;
    tx_message.command_id =  (unsigned char)command_Code;
    tx_message.slave_reg_addr=(unsigned short int )command_reg_addr;
    //tx_message.data[0]=len;

    if(len > 0)
    {
        memcpy(&tx_message.data[0] , p , len);
    }
    switch (command_Code)
    {
    case READ_REG :
        Request03(&tx_message);
        break;

    case READ_INPUT_REG :

        Request04(&tx_message);
 
        break;

    case WRITE_REG :
        Request06(&tx_message);

        break;
        
    case WRITE_MORE_REG :
        Request16(&tx_message,len);
        break;

    default :
        break;
    }
}


