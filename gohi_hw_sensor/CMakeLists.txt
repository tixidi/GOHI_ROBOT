cmake_minimum_required(VERSION 2.8.3)
project(gohi_hw_sensor)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  controller_manager
  geometry_msgs
  hardware_interface
  realtime_tools
  roscpp
  std_msgs
  gohi_msgs
  message_runtime 
  serial
  message_generation
)

add_message_files(
  FILES
  Puncture.msg
)
generate_messages(
  DEPENDENCIES std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES gohi_hw_sensor
  CATKIN_DEPENDS   message_runtime
  DEPENDS system_lib
)


include_directories(
  include 
  ${catkin_INCLUDE_DIRS}
  include/sdk/hf_link/
  include/sdk/robot_abstract/
  include/gohi_hw/
  include/gohi_hw_sersor/
  /usr/include/alsa

)



add_executable(gohi_hw_node_sensor src/main.cpp src/HIGO_ROS.cpp src/transport_serial.cpp src/HIGO_AP.cpp include/sdk/hf_link/hf_link_modbus.cpp include/sdk/hf_link/hf_link_state_machine_modbus.cpp include/sdk/hf_link/robot_control.cpp)
add_dependencies(gohi_hw_node_sensor  gohi_msgs_gencpp)
target_link_libraries(gohi_hw_node_sensor ${catkin_LIBRARIES})

add_executable(serial_example_node src/serial_example.cpp src/crc.cpp)
add_dependencies(serial_example_node ${catkin_EXPORTED_TARGETS} ${gohi_hw_sensor_EXPORTED_TARGETS})
target_link_libraries(serial_example_node ${catkin_LIBRARIES})

add_executable(talker_node src/talker.cpp)
add_dependencies(talker_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(talker_node ${catkin_LIBRARIES})

add_executable(listener_node src/listener.cpp)
add_dependencies(listener_node ${catkin_EXPORTED_TARGETS} ${gohi_hw_sensor_EXPORTED_TARGETS})
target_link_libraries(listener_node ${catkin_LIBRARIES})

