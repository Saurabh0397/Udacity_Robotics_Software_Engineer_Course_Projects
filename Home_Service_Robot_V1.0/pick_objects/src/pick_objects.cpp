   #include <ros/ros.h>
   #include <move_base_msgs/MoveBaseAction.h>
   #include <actionlib/client/simple_action_client.h>
   
   typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
   
   int main(int argc, char** argv){
     ros::init(argc, argv, "pick_objects");
   
     //tell the action client that we want to spin a thread by default
     MoveBaseClient ac("move_base", true);
   
     //wait for the action server to come up
     while(!ac.waitForServer(ros::Duration(5.0))){
       ROS_INFO("Waiting for the move_base action server to come up");
     }
   
     move_base_msgs::MoveBaseGoal goal;
   
     //we'll send a goal to the robot to move 1 meter forward
     goal.target_pose.header.frame_id = "map";
     goal.target_pose.header.stamp = ros::Time::now();
   
     goal.target_pose.pose.position.x = -2.5;
     goal.target_pose.pose.position.x = -2.5;
     goal.target_pose.pose.orientation.w = 1.0;
   
     ROS_INFO("Sending goal");
     ac.sendGoal(goal);
   
     ac.waitForResult();
   
     if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
     {
       ROS_INFO("The bot successfully moved to the first position");


       //pause for 5 seconds and then move to second position
	ros::Duration(5.0).sleep();

       //go to second/final position
       move_base_msgs::MoveBaseGoal goal;
       goal.target_pose.header.frame_id = "map";
       goal.target_pose.header.stamp = ros::Time::now();


       goal.target_pose.pose.position.x = -5.0;
       goal.target_pose.pose.position.x = -5.0;
       goal.target_pose.pose.orientation.w = 1.0;

       ROS_INFO("Sending goal");
       ac.sendGoal(goal);
       ac.waitForResult();

       if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
       {
            ROS_INFO("The bot successfully moved to the second/final position");
       } 
       else 
       {
           ROS_INFO("The bot failed to move to the second/final position");
       }

     } 
     else
     {
       ROS_INFO("The bot failed to move to the first position");
     }
     return 0;
   }
