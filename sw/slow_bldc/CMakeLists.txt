cmake_minimum_required(VERSION 2.8.3)
project(slow_bldc)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  message_generation
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(cfg/Driver.cfg)

add_message_files(FILES
  IntParam.msg
  FloatParam.msg
)

add_service_files(FILES
  SetIntParam.srv
  SetFloatParam.srv
)

generate_messages()

catkin_package(
  CATKIN_DEPENDS
    roslib
    sensor_msgs
    message_runtime
#  INCLUDE_DIRS include
#  LIBRARIES falcam
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(slow_bldc slow_bldc.cpp lightweightserial.cpp)
add_dependencies(slow_bldc
  slow_bldc_gencfg
  ${slow_bldc_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(slow_bldc ${catkin_LIBRARIES})

#############
## Install ##
#############

install(TARGETS slow_bldc
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

