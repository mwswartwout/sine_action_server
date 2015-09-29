#include <ros/ros.h>
#include <iostream>
#include "sine_action_client.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "sine_action_client");
    actionlib::SimpleActionClient<sine_action_server::sine_control> action_client("sine_control", true);
    
    ROS_INFO("waiting for server: ");
    bool server_exists = action_client.waitForServer(ros::Duration(5.0));
    
    if (!server_exists) {
        ROS_WARN("could not connect to server; halting");
        return 0;
    }

    ROS_INFO("connected to action server");

    double entry;
    bool finishedBeforeTimeout;
    while (ros::ok) {
        std::cout << std::endl;
        std::cout << "Enter an amplitude (x to quit)";
        std::cout << std::endl;
        std::cin >> entry; // Get which variable user wants to change and save in type
        std::cout << std::endl;
        if (type.compare("x") == 0) {
            return 0; // Exit if user typed "x"
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
        
        action_client.sendGoal(goal);
    }
}
