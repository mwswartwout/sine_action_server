#include <ros/ros.h>
#include <iostream>
#include "sine_action_client.h"

bool SineActionClient::getGoals() {
    double entry;
 
    std::cout << "Enter an amplitude (< 0 to quit)";
    std::cout << std::endl;
    std::cin >> entry; // Get which variable user wants to change and save in type
    std::cout << std::endl;
    if (entry < 0) {
        return true; // Exit if user typed a negative number 
    }
    goal.amplitude = entry;

    std::cout << "Enter a frequency";
    std::cout << std::endl;
    std::cin >> entry; // Get which variable user wants to change and save in type
    std::cout << std::endl;
    goal.frequency = entry;

    std::cout << "Enter the number of cycles";
    std::cout << std::endl;
    std::cin >> entry; // Get which variable user wants to change and save in type
    std::cout << std::endl;
    goal.cycles = entry;

    return false;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "sine_action_client"); // init node
    actionlib::SimpleActionClient<sine_action_server::sine_controlAction> action_client("sine_control", true); // init ActionClient
    SineActionClient ac_object;

    ROS_INFO("waiting for server: ");
    bool server_exists = action_client.waitForServer(ros::Duration(5.0));
    
    if (!server_exists) {
        ROS_WARN("could not connect to server; halting");
        return 0;
    }

    ROS_INFO("connected to action server");
    bool finished = false;
    while (ros::ok && !finished) {
        finished = ac_object.getGoals();
        if (!finished) { 
            action_client.sendGoal(ac_object.goal);    
        }
        else {
            return 0;
        } 
    }

    return 0;
}
