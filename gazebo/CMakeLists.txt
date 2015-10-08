cmake_minimum_required(VERSION 2.8.3)
project(nostop_robot_gazebo)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)

catkin_package(
  INCLUDE_DIRS include/${PROJECT_NAME}/
)

include_directories(include/${PROJECT_NAME}/ ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${SDFormat_INCLUDE_DIRS})

# Build whatever you need here
#add_library(...) # TODO

catkin_package(
    DEPENDS
      gazebo_ros
      roscpp
    CATKIN_DEPENDS
    INCLUDE_DIRS
    LIBRARIES
)

add_executable(${PROJECT_NAME} src/example.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})