#include "robot_planners/planner_ee.h"

//namespace planners {
/*
Planner_ee::Planner_ee(Base_EE_Planner& ee_planner, ros::NodeHandle &nh, const asrv::Action_ee_initialiser &action_ee_init):
    ee_planner(ee_planner),
    Base_ee_action(nh,
                   action_ee_init.ee_state_pos_topic,
                   action_ee_init.ee_cmd_pos_topic,
                   action_ee_init.ee_cmd_ft_topic)
{

    reachingThreshold       = action_ee_init.reachingThreshold;     // [m]
    orientationThreshold    = action_ee_init.orientationThreshold;  // [rad]

    initial_config          = true;
    tf_count                = 0;
    dt                      = 1.0/100.0;
    default_speed           = 0.001; // [m/s]

}


bool Planner_ee::execute_CB(asrv::alib_server& as_,asrv::alib_feedback& feedback,const asrv::cptrGoal& goal){


    tf::Transform trans_att;

    trans_att.setRotation(tf::Quaternion(goal->attractor_frame.rotation.x,goal->attractor_frame.rotation.y,
                                         goal->attractor_frame.rotation.z,goal->attractor_frame.rotation.w));
    trans_att.setOrigin(tf::Vector3(goal->attractor_frame.translation.x, goal->attractor_frame.translation.y,
                                    goal->attractor_frame.translation.z));

    ros::Rate wait(1);
    tf::Vector3     current_origin = ee_pose.getOrigin();
    tf::Quaternion  current_orient = ee_pose.getRotation();


    tf::Vector3    target_pos    = trans_att.getOrigin();
    tf::Quaternion target_orient = trans_att.getRotation();

    ROS_INFO("current_origin (%f %f %f)",current_origin.x(),current_origin.y(),current_origin.z());
    ROS_INFO("current_target (%f %f %f)",target_pos.x(),target_pos.y(),target_pos.z());

    tf::Vector3    velocity;

    double rate;
    if(goal->dt > 0){
        rate = 1.0/(goal->dt);
    }else{
        rate = 1.0/dt;
    }

    double max_speed =  default_speed; // [ms]
    double speed;
    double dist_targ_origin = (target_pos - current_origin).length();
    double dist_targ_target = current_orient.dot(target_orient);
    double max_dist         = dist_targ_origin;
    double slerp_t          = 0.5;
    double beta             = (1.0/10.0);
    double offset           = 0;
    double prev_orient_error  = 0.0; //[rad]

    ROS_INFO("distance_origin_target %f",dist_targ_origin);
    ROS_INFO("distance_orient_target %f",dist_targ_target);
    ROS_INFO("max_dist %f",max_dist);
    ROS_INFO("max_speed %f [m/s]",max_speed);
    ROS_INFO("rate %f",rate);


    static tf::TransformBroadcaster br;
    ros::Rate loop_rate(rate);

    bool success = true;

    while(ros::ok()) {

        /*br.sendTransform(tf::StampedTransform(trans_att, ros::Time::now(), world_frame, "ee_final"));


        current_origin = ee_pose.getOrigin();
        current_orient = ee_pose.getRotation();


        // Linear velocity between start position and target
        velocity = (target_pos - current_origin);

        // compute desired speed (function of distance to goal, bell shapped velocity curve)
        dist_targ_origin = velocity.length(); // [meters]
        speed            = (max_speed * bell_velocity(dist_targ_origin * 100.0,beta,offset));    // convert [m] -> [cm]
        velocity         = speed * velocity.normalize();

        des_ee_pose.setOrigin(velocity + current_origin);
        des_ee_pose.setRotation( current_orient.slerp(target_orient, slerp_t)      );

        dist_targ_target = acos(abs(target_orient.dot(current_orient)));
        sendPose(des_ee_pose);

        feedback.progress = dist_targ_target;
        as_.publishFeedback(feedback);
        if (as_.isPreemptRequested() || !ros::ok())
        {
            ROS_INFO("Preempted");
            as_.setPreempted();
            success = false;
            break;
        }

        float diff_ori_err = abs(dist_targ_target - prev_orient_error);
        ROS_INFO_STREAM("Distance to target origin: " << dist_targ_origin << " reachingThreshold: " << reachingThreshold );
        ROS_INFO_STREAM("Distance to target orient: " << dist_targ_target << " orientationsThreshold: " << orientationThreshold );
        ROS_INFO_STREAM("Difference in Orientation error: " << diff_ori_err);

        if (( dist_targ_origin < reachingThreshold) && (dist_targ_target < orientationThreshold || std::isnan(dist_targ_target) || diff_ori_err < 0.001) ){
            ROS_INFO("reached goal");
            break;
        }

        prev_orient_error = dist_targ_target; //[rad]
        loop_rate.sleep();*/
    }
/*
    return success;



}
*/


//}
