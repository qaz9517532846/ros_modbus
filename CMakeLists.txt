cmake_minimum_required(VERSION 3.0.2)
project(ros_modbus)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package(
#   INCLUDE_DIRS include
#  LIBRARIES ros_modbus
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  /usr/local/include/modbus
)

add_executable(ros_modbus_tcp src/ros_modbus_tcp.cpp)
target_link_libraries(ros_modbus_tcp ${catkin_LIBRARIES})
target_link_libraries(ros_modbus_tcp /usr/local/lib/libmodbus.so)