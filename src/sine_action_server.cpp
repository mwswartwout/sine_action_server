#include <ros/ros.h>
#include "sine_action_server.h"
#include <std_msgs/Float64.h>
#include <math.h>
#include <Sinusoid_Controller_With_Services/sinecontrol.h>

SineActionServer::SineActionServer() : as(n, "sine_control", boost::bind(&SineActionServer::executeCB, this, _1), false) {
    ROS_INFO("In constructor of SineActionServer");
    as.start();
}

void SineActionServer::executeCB(const actionlib::SimpleActionServer<sine_action_server::sine_control>::GoalConstPtr& goal) {
    ROS_INFO("Received frequency %f", goal.frequency);
    frequency = goal.frequency; // Set frequency to value in request
    
    ROS_INFO("Received amplitude %f", goal.amplitude);
    amplitude = goal.amplitude; // Set amplitude to value in request
    
    ROS_INFO("Received number of cycles %f", goal.numCycles);
    cycles = goal.cycles;

    feedback.complete = false; // indicate new message received and hasn't been completed 

    while (currentTime - startTime < cycles / frequency) {
        sine = amplitude * sin(2*pi*frequency*currenTime); // Calculate sine value
        output.data = sine; // Store sine value in proper message format
        command_publisher.publish(output); // Publish value to vel_cmd topic
        t += dt; // Increment t by timeset dt
        naptime.sleep(); // Then sleep to keep updating to specified interval
    }

    amplitude = 0;
    frequency = 0;
    feedback.complete = true; // everything is complete
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "services_commander"); // services_commander node
    command_publisher = n.advertise<std_msgs::Float64>("vel_cmd", 1); // publish to vel_cmd topic
    service = n.advertiseService("sine_control", callback);
    naptime(10); // update @ 10hz

    amplitude = 0; // amplitude value for sine wave
    frequency = 0; // frequency value for sine wave
    pi = 3.14159; // value of pi
    currentTime = 0; // current time in calculation
    dt = naptime.expectedCycleTime(); // timestep for calculation
    sine = 0; // sine output
    startTime = 0;

    ROS_INFO("Ready to set amplitude and frequency");
    
    while (ros::ok()) {
        ros::spin();
    } 

    return 0;
}
