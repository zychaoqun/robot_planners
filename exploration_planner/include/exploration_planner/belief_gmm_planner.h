#ifndef BELIEF_GMM_EXPLORATION_PLANNER_H_
#define BELIEF_GMM_EXPLORATION_PLANNER_H_

/**
       Simple belief state

       Forms a plan by considering a single hypothetical state (x,y,z) from the belief p(x).
       The belief is in terms of the position of the end-effector and the beliefs
       parameterisation is not important for this implemenation.

       - The planner subscribs to a topic which provides a plossible true hypothetical
         state of the location of the end-effector.

       - Tipical belief information pip-line:
             particle_filter -> feature extraction -> hypothetical position (x,y,z)

  **/

#include <ros/ros.h>
#include <kuka_action_server/action_server.h>
#include <kuka_action_server/base_ee_action.h>
#include <kuka_common_action_server/action_initialiser.h>
#include <std_msgs/Float64MultiArray.h>

#include <visualise/vis_points.h>
#include <exploration_planner/String_cmd.h>
#include <optitrack_rviz/listener.h>

#include <armadillo>

#include "statistics/distributions/gmm.h"
#include "robot_planners/gmmPlanner.h"
#include <optitrack_rviz/listener.h>

#include "peg_sensor/listener.h"



namespace belief{

class Gmm_planner : public asrv::Base_ee_action, public asrv::Base_action_server{

public:

    Gmm_planner(ros::NodeHandle&   nh,
                   const std::string& topic_name,
                   const std::string& world_frame,
                   string path_parameters,
                   const asrv::Action_ee_initialiser &action_ee_init);

    virtual bool execute_CB(asrv::alib_server& as_,asrv::alib_feedback& feedback,const asrv::cptrGoal& goal);

private:


    bool service_callback(exploration_planner::String_cmd::Request& req,exploration_planner::String_cmd::Response& res);

    void topic_callback(const std_msgs::Float64MultiArrayConstPtr& msg);

    inline double bell_velocity(double x,double beta,double off){
        return 1.0 - exp(-beta * (x+off) * (x+off));
    }


private:

    planners::GMAPlanner    gmap_planner;

    ros::Subscriber         belief_info_sub; /// subscriber to
    tf::Vector3             hx_current_origin; /// arg max{p(x)}, E{p(x)}, ...s
    tf::Quaternion          current_orient;

    tf::Pose                des_ee_pose;    /// desired end-effector position


    tf::Transform            virtual_end_effector;

    std::string              world_frame;

    ros::ServiceServer       service_server;

    psm::Peg_sensor_listener  peg_sensor_listener;


    double                   dt;
    double                   dist_targ_target;

    double                   reachingThreshold;
    double                   orientationThreshold;
    double                   default_speed;

    bool                     bSimulation;
    bool                     bPause;

};

}

#endif