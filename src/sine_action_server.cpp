#include <ros/ros.h>
#include "sine_action_server.h"
#include <math.h>

SineActionServer::SineActionServer() : 
    as(n, "sine_control", boost::bind(&SineActionServer::executeCB, this, _1), false) 
{
    ROS_INFO("In constructor of SineActionServer");

    command_publisher = n.advertise<std_msgs::Float64>("vel_cmd", 1); // publish to vel_cmd topic
    ros::Rate naptime(10); //  = ros::Rate(10);
    amplitude = 0; // amplitude value for sine wave
    frequency = 0; // frequency value for sine wave
    pi = 3.14159; // value of pi
    currentTime = 0; // current time in calculation
    dt = naptime.expectedCycleTime().toSec(); // timestep for calculation
    sine = 0; // sine output
    startTime = 0;

    as.start();
}

void SineActionServer::executeCB(const actionlib::SimpleActionServer<sine_action_server::sine_controlAction>::GoalConstPtr& goal) {
    ROS_INFO("Received frequency %f", goal->frequency);
    frequency = goal->frequency; // Set frequency to value in request
    
    ROS_INFO("Received amplitude %f", goal->amplitude);
    amplitude = goal->amplitude; // Set amplitude to value in request
    
    ROS_INFO("Received number of cycles %f", goal->cycles);
    cycles = goal->cycles;

    //feedback->complete = false; // indicate new message received and hasn't been completed 
    ros::Rate naptime(10);
    startTime = currentTime;
    while (currentTime - startTime < cycles / frequency) {
        sine = amplitude * sin(2*pi*frequency*currentTime); // Calculate sine value
        output.data = sine; // Store sine value in proper message format
        command_publisher.publish(output); // Publish value to vel_cmd topic
        currentTime += dt; // Increment t by timeset dt
        naptime.sleep(); // Then sleep to keep updating to specified interval
    }

    amplitude = 0;
    frequency = 0;
    as.setSucceeded();
    //feedback.complete = true; // everything is complete
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "services_commander"); // services_commander node
    SineActionServer as_object;
 
    ROS_INFO("Ready to set amplitude and frequency");
    while (ros::ok()) {
        ros::spin();
    } 

    return 0;
}
