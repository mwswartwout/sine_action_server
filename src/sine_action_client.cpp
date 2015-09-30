#include <ros/ros.h>
#include <iostream>
#include "sine_action_client.h"

bool SineActionClient::getGoals() {
    bool finished = false;
    double entry;
 
    std::cout << "Enter an amplitude (-1 to quit)";
    std::cout << std::endl;
    std::cin >> entry; // Get which variable user wants to change and save in type
    std::cout << std::endl;
    if (entry == -1) {
        finished = true; // Exit if user typed "x"
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
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "sine_action_client");
    actionlib::SimpleActionClient<sine_action_server::sine_controlAction> action_client("sine_control", true);
    SineActionClient ac_object;

    ROS_INFO("waiting for server: ");
    bool server_exists = action_client.waitForServer(ros::Duration(5.0));
    
    if (!server_exists) {
        ROS_WARN("could not connect to server; halting");
        return 0;
    }

    ROS_INFO("connected to action server");

    bool finishedBeforeTimeout;
    while (ros::ok) {
        if (!ac_object.getGoals()) { 
            action_client.sendGoal(ac_object.goal);
        }
        else {
            return 0;
        }
    }

    return 0;
}
