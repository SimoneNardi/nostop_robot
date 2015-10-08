#include <ros/ros.h>

#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/GetModelState.h>
#include <gazebo_msgs/SpawnModel.h>

#include <iostream>
#include <string>
#include <fstream>

int main (int argc, char** argv)
{
  ros::init(argc,argv,"test_node");
  ros::NodeHandle n;
  
  ///
  ros::ServiceClient clientSpawn = n.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_urdf_model"); 
  gazebo_msgs::SpawnModel spawnModel;
  spawnModel.request.model_name = "my_bot";
  //~
  std::string l_name = "/home/simone/catkin_ws/src/nostop/nostop_robot/description/urdf/model.urdf";
  std::ifstream inFile (l_name.c_str());
  if (inFile.is_open())
  {
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string str = buffer.str();
    spawnModel.request.model_xml = str.c_str();
    ROS_INFO("%s",str.c_str());
  }
  
  spawnModel.request.initial_pose.position.x = -1;
  spawnModel.request.initial_pose.position.y = 0;
  spawnModel.request.initial_pose.position.z = 0;
  spawnModel.request.initial_pose.orientation.z = 3.14/4;
      
  if (clientSpawn.call(spawnModel))
  {
    if( spawnModel.response.success )
      ROS_INFO("BRILLIANT!!!");
    else
      ROS_INFO("BAD!!!");
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }
  
  ///
  ros::ServiceClient clientSet = n.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state"); 
  gazebo_msgs::SetModelState setmodelstate;
  gazebo_msgs::ModelState modelstate;
  modelstate.model_name = spawnModel.request.model_name;
  modelstate.pose.position.x = 0;
  modelstate.pose.position.y = 0;
  modelstate.pose.position.z = 0;
  
  modelstate.twist.angular.z = 0;
  modelstate.twist.linear.x = .5;
  //modelstate.twist.linear.y = .5*sin(30);
  
  setmodelstate.request.model_state= modelstate;
  
  if (clientSet.call(setmodelstate))
  {
    if (setmodelstate.response.success)
      ROS_INFO("BRILLIANT!!!");
    else
      ROS_INFO("BAD!!!");
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }
  
  ///
  ros::ServiceClient clientGet = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state"); 
  gazebo_msgs::GetModelState getmodelstate;
  getmodelstate.request.model_name = spawnModel.request.model_name;
  
  if (clientGet.call(getmodelstate))
  {
    ROS_INFO("BRILLIANT!!!");
    ROS_INFO("%f",getmodelstate.response.pose.position.x);
    ROS_INFO("%f",getmodelstate.response.pose.position.y);
    ROS_INFO("%f",getmodelstate.response.pose.position.z);
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }
  return 0;
}