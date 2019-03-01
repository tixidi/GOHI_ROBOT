#pragma once

#ifndef HIGO_AP_H_
#define HIGO_AP_H_

#include <fstream>
// #include <gohi_hw/transport_serial.h>
#include <gohi_hw/transport_tcp.h>
#include <hf_link_modbus.h>
#include <cstdlib>

class HIGO_AP
{
public:
	 HIGO_AP(std::string url, std::string config_addr);
    unsigned char  send_sensor_flag_;
 //   bool updateCommand(const Command &command, int count);
    bool updateCommand(const MotorModbusCommand &command, int count);
    bool updateCommand(const MotorModbusCommand &command, int count,int read_or_write);

    


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

    // inline void checkHandshake()
    // {
    //     if (hflink_->getReceiveRenewFlag(SHAKING_HANDS)==1)
    //     {
    //         sendCommand(SHAKING_HANDS);
    //         std::cout<<"send shake hands"<<std::endl;
    //     }
    // }
    inline void sendCommandModbus(const MotorModbusCommand command_state)
    {
        hflinkmodbus_->masterSendCommand(command_state);
        Buffer data(hflinkmodbus_->getSerializedData(), hflinkmodbus_->getSerializedLength() + hflinkmodbus_->getSerializedData());
        client_tcp_->writeBuffer(data);
    }


 //first modify***************************
    inline void readCommandModbus0()
    {
        boost::asio::deadline_timer cicle_timer_(io_service);
         cicle_timer_.expires_from_now(boost::posix_time::millisec(time_out_));
        Buffer data=client_tcp_->readBuffer();   
        // std::cerr << "read3:"<< data.size()<<std::endl;
        ack_ready_ = false;
        while (!ack_ready_)
        {
            for (int i = 0; i < data.size(); i++)
            {    
                if (hflinkmodbus_->byteAnalysisCall_R(data[i]))
                {
                    std::cerr << "read is ok"<<std::endl;
                    // one package ack arrived  
                    ack_ready_ = true;         
                }
            }
            data = client_tcp_->readBuffer();
            if (cicle_timer_.expires_from_now().is_negative())
            {
                std::cerr<<"Timeout continue skip this package"<<std::endl;
                return;
            }
        }
    }

    inline void readCommandModbus1()
    {
        boost::asio::deadline_timer cicle_timer_(io_service);
         cicle_timer_.expires_from_now(boost::posix_time::millisec(time_out_));
        Buffer data=client_tcp_->readBuffer();   
        // std::cerr << "read3:"<< data.size()<<std::endl;
        ack_ready_ = false;
        while (!ack_ready_)
        {
            for (int i = 0; i < data.size(); i++)
            {    
                if (hflinkmodbus_->byteAnalysisCall(data[i]))
                {
                    std::cerr << "read is ok"<<std::endl;
                    // one package ack arrived  
                    ack_ready_ = true;         
                }
            }
            data = client_tcp_->readBuffer();
            if (cicle_timer_.expires_from_now().is_negative())
            {
                std::cerr<<"Timeout continue skip this package"<<std::endl;
                return;
            }
        }
    }

private:
   //first modify***************************
    boost::shared_ptr<client> client_tcp_;
    boost::asio::io_service io_service;
    // boost::shared_ptr<Transport> port_;


 //   boost::shared_ptr<HFLink> hflink_;
    boost::shared_ptr<HFLink_Modbus> hflinkmodbus_;
    
    boost::shared_ptr<boost::asio::deadline_timer> timer_;

    //for reading config file
    std::fstream file_;
    bool initialize_ok_;
    //for updating data
    // int hflink_command_set_[LAST_COMMAND_FLAG];
    // int hflink_freq_[LAST_COMMAND_FLAG];
    // int hflink_count_[LAST_COMMAND_FLAG];
    // int hflink_command_set_current_[LAST_COMMAND_FLAG];

    int hflink_command_set_[LAST_COMMAND_FLAG_];
    int hflink_freq_[LAST_COMMAND_FLAG_];
    int hflink_count_[LAST_COMMAND_FLAG_];
    int hflink_command_set_current_[LAST_COMMAND_FLAG_];


    int time_out_;
    bool time_out_flag_;

    
    boost::mutex wait_mutex_;
    bool ack_ready_;
    void timeoutHandler(const boost::system::error_code &ec);

    // inline uint8_t checkUpdate(const Command command_state)
    // {
    //     if (hflink_command_set_current_[command_state] & hflink_->getReceiveRenewFlag(command_state))
    //     {
    //         return 1;
    //     }
    //     if (hflink_command_set_current_[command_state] == 0 ) return 1;
    //     return 0;
    // }




    // a single object for robot
    RobotAbstract my_robot_;

};



#endif
