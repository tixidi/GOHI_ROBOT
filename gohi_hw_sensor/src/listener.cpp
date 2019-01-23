/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/String.h"

#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "crc.h"

#include "geometry_msgs/Accel.h"
#include "gohi_hw_sensor/Puncture.h"

//crc::CRC cc_crc;
//回调函数
class Listener
{
  public:
  //void callback(const std_msgs::UInt8MultiArray::ConstPtr& r_buffer);
  void callback(const gohi_hw_sensor::Puncture &r_buffer);
};
//void Listener::callback(const std_msgs::UInt8MultiArray::ConstPtr& r_buffer)
void Listener::callback(const gohi_hw_sensor::Puncture &r_buffer)
{
  // ROS_INFO("Received a /Accel message!");
	// ROS_INFO("Linear Components:[%f,%f,%f]",r_buffer.linear.x,r_buffer.linear.y,r_buffer.linear.z);
	// ROS_INFO("Angular Components:[%f,%f,%f]",r_buffer.angular.x,r_buffer.angular.y,r_buffer.angular.z);
  // ROS_INFO("Received a /Puncture message!");
	ROS_INFO("Puncture message:[%d,%d,%d]",r_buffer.Puncture_id,r_buffer.Puncture_cmd,r_buffer.Puncture_data);
  //ROS_INFO("listener heard:x=%f y=%f",r_buffer.linear.x,r_buffer.linear.y);
  //ROS_INFO("listener heard: %x %x %x %x %x %x %x %x %x",r_buffer->data[0],r_buffer->data[1],r_buffer->data[2],r_buffer->data[3],r_buffer->data[4],r_buffer->data[5],r_buffer->data[6],r_buffer->data[7],r_buffer->data[8]);
  
  // if(r_buffer->data[1]==0x01)
  // {
  //   //ROS_INFO("I heard:");//, serial_data->data);
  //   ROS_INFO("listener heard: %x %x %x %x %x %x %x %x %x",r_buffer->data[0],r_buffer->data[1],r_buffer->data[2],r_buffer->data[3],r_buffer->data[4],r_buffer->data[5],r_buffer->data[6],r_buffer->data[7],r_buffer->data[8]);
  // }
  // else
  // {
  //   ROS_INFO("wrong");//, serial_data->data);
  // }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  //订阅主题
  Listener listener;
  ros::Subscriber sub = n.subscribe("read", 1000, &Listener::callback, &listener);
  //ros::Publisher sensor_pub = n.advertise<std_msgs::UInt8MultiArray>("sensor", 1000);
  ros::spin();
  return 0;
}
