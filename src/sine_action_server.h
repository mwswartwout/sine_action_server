#ifndef SINE_ACTION_SERVER_H
#define SINE_ACTION_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <sine_action_server/sine_controlAction.h>
#include <std_msgs/Float64.h>

class SineActionServer {
private:
    ros::Publisher command_publisher;
    ros::NodeHandle n;
    ros::ServiceServer service;
    ros::Rate naptime; 
    actionlib::SimpleActionServer<sine_action_server::sine_controlAction> as;
    sine_action_server::sine_controlGoal goal;
    std_msgs::Float64 output; // message wrapper for sine output
    SineActionServer server(); // start the serversine_action_server::sine_controlFeedback feedback;
    double amplitude;
    double frequency;
    double cycles;
    double currentTime;
    double startTime;
    double pi;
    double dt;
    double sine;

public:
    SineActionServer();
    void executeCB(const actionlib::SimpleActionServer<sine_action_server::sine_controlAction>::GoalConstPtr& goal);
};
#endif        
