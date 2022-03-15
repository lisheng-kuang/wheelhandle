/* headers for ROS */
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt16MultiArray.h>
#include <std_msgs/MultiArrayDimension.h>
#include <sstream>
#include <iostream>

using namespace std;
/* Topology for the JND command:
 *
 *  */
int cnt = 0;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "pub_servomotor_cmd");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::UInt16MultiArray>("servomotor_cmd", 1000);
    ros::Rate loop_rate(1);

    int motorX = 0;
    int motorY = 0;

    while (ros::ok())
    {
        std_msgs::UInt16MultiArray servomotor_msg;
        /* manually input the motor x angle (0~180) */
        servomotor_msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
        servomotor_msg.layout.dim[0].size = 2;
        servomotor_msg.layout.dim[0].stride = 1;
        servomotor_msg.layout.data_offset = 0;
        if (cnt > 180)
        {
            cnt = 0;
        }
        servomotor_msg.data.push_back(cnt);
        servomotor_msg.data.push_back(180 - cnt);

        ROS_INFO("data0 = %d", servomotor_msg.data[0]);
        ROS_INFO("data1 = %d", servomotor_msg.data[1]);
        ROS_INFO("data2 = %d", servomotor_msg.data[2]);
        chatter_pub.publish(servomotor_msg);
        cnt += 5;

        ros::spinOnce();

        // ros::spin();

        loop_rate.sleep();
    }

    return 0;
}
