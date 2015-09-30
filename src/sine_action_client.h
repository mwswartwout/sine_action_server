#ifndef SINE_ACTION_CLIENT_H
#define SINE_ACTION_CLIENT_H

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <sine_action_server/sine_controlAction.h>

class SineActionClient {
    public:
        sine_action_server::sine_controlGoal goal;
        void getGoals(); 
};
#endif
