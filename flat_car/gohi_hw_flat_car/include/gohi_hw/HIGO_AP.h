#pragma once

#ifndef HIGO_AP_H_
#define HIGO_AP_H_
#include <fstream>
#include <ros/ros.h>
//first modify***************
// #include <gohi_hw/transport_serial.h>
#include <gohi_hw/transport_tcp.h>

#include <hf_link_modbus.h>
#include <cstdlib>

class HIGO_AP
{
public:
	 HIGO_AP(std::string url, std::string config_addr);

 //   bool updateCommand(const Command &command, int count);
    bool updateCommand(const MotorModbusCommand &command, int count);
    bool updateCommand( const MotorModbusCommand &command,int &count,int read_or_write);

    

    void updateRobot();

    inline RobotAbstract* getRobotAbstract()
    {
        return &my_robot_;
    }

    inline boost::shared_ptr<boost::asio::io_service> getIOinstace()
    {
        return client_tcp_->getIOinstace();
    }

    bool reconfig()
    {

    }

    inline bool initialize_ok () const
    {
        return initialize_ok_;
    }



private:
//first modify *************************
    // boost::shared_ptr<Transport> port_;
    boost::shared_ptr<client> client_tcp_;
    boost::asio::io_service io_service;

 //   boost::shared_ptr<HFLink> hflink_;
    boost::shared_ptr<HFLink_Modbus> hflinkmodbus_;
    
    boost::shared_ptr<boost::asio::deadline_timer> timer_;

    //for reading config file
    std::fstream file_;
    bool initialize_ok_;


    int hflink_command_set_[LAST_COMMAND_FLAG_];
    int hflink_freq_[LAST_COMMAND_FLAG_];
    int hflink_count_[LAST_COMMAND_FLAG_];
    int hflink_command_set_current_[LAST_COMMAND_FLAG_];


    int write_time_out_;
    int read_time_out_;
    bool time_out_flag_;
    boost::mutex wait_mutex_;
    bool ack_ready_;
    void timeoutHandler(const boost::system::error_code &ec);



    inline void sendCommandModbus(const MotorModbusCommand command_state)
    {
        hflinkmodbus_->masterSendCommand(command_state);
        Buffer data(hflinkmodbus_->getSerializedData(), hflinkmodbus_->getSerializedLength() + hflinkmodbus_->getSerializedData());
        client_tcp_->writeBuffer(data);
        for(int i=0;i<data.size();i++){
            if(command_state == SET_CAR1_LEFT_SPEED_CONTROL){
                std::cerr << "write motor1 :"<< (uint16_t)data[i]<<std::endl;
            }else if(command_state == SET_CAR1_RIGHT_SPEED_CONTROL)
                std::cerr << "write motor2:"<< (uint16_t)data[i]<<std::endl;
        }
    }


 //first modify**0*************************
    inline void readCommandModbus0(const MotorModbusCommand &command)
    {
         static int time_out_count=0;
         boost::asio::deadline_timer cicle_timer_(io_service);
         cicle_timer_.expires_from_now(boost::posix_time::millisec(read_time_out_));
        Buffer data=client_tcp_->readBuffer();   
        //  std::cerr << "read:"<< time_out_count++ <<"  "<<time_out_<<std::endl;
        ack_ready_ = false;
        while (!ack_ready_)
        {
            for (int i = 0; i < data.size(); i++)
            {    
                if (hflinkmodbus_->byteAnalysisCall_R(data[i]))
                {
                    // hflinkmodbus_->rev_packetage =1;
                    std::cerr << "read is ok"<<std::endl;
                    // one package ack arrived  
                    ack_ready_ = true;         
                }
            }
            data = client_tcp_->readBuffer();
            if (cicle_timer_.expires_from_now().is_negative())
            {
                if(command == READ_MOT1_REAL_POSITION){
                    hflinkmodbus_->rev_packetage_mot1 =2;
                }else if(command == READ_MOT2_REAL_POSITION)
                    hflinkmodbus_->rev_packetage_mot2 =2;
                
                std::cerr<<"read Timeout continue skip this package"<<std::endl;
                time_out_count=0;
                return;
            }
        }
    }
    inline void readCommandModbus1(const MotorModbusCommand &command)
    {
        boost::asio::deadline_timer cicle_timer_(io_service);
        cicle_timer_.expires_from_now(boost::posix_time::millisec(write_time_out_));
        Buffer data=client_tcp_->readBuffer();   
        ros::Time currentTime = ros::Time::now();
       std::cerr<<"read:::"<<std::endl;
        ack_ready_ = false;
        while (!ack_ready_)
        {
            for (int i = 0; i < data.size(); i++)
            {     
                


                if(command == SET_CAR1_LEFT_SPEED_CONTROL){
                   std::cerr << " read motor1 :"<< (uint16_t)data[i]<<std::endl;
                }else if(command == SET_CAR1_RIGHT_SPEED_CONTROL)
                    std::cerr << "read motor2:"<< (uint16_t)data[i]<<std::endl;

                if (hflinkmodbus_->byteAnalysisCall(data[i]))
                {
                    // hflinkmodbus_->rev_packetage =1;
                     std::cerr << "write is ok"<<std::endl;
                    // one package ack arrived  
                    ack_ready_ = true;         
                }
            }
            data = client_tcp_->readBuffer();
            //  std::cerr<< "spend time is  " << (float)(ros::Time::now() - currentTime).toSec() <<std::endl;
            if (cicle_timer_.expires_from_now().is_negative())
            {
                if(command == SET_CAR1_LEFT_SPEED_CONTROL){
                   std::cerr<<"SET_CAR1_LEFT_SPEED_CONTROL write Timeout continue skip this package"<<std::endl;
                }else if(command == SET_CAR1_RIGHT_SPEED_CONTROL)
                    std::cerr<<"SET_CAR1_RIGHT_SPEED_CONTROL write Timeout continue skip this package"<<std::endl;
                
                return;
            }
        }
    }  

    // a single object for robot
    RobotAbstract my_robot_;

};



#endif
