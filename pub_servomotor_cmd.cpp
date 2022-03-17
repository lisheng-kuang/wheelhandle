/**
 * this file can work with the arduino
 * on the arduino side, run this: rosrun rosserial_python serial_node.py /dev/ttyUSB0
 * this side: rosrun wheelchairhandle pub_servomotor_cmd_node
 * **/
/* headers for ROS */

/***************************** do with UInt16MultiArray  ********************/
// #include <iostream>
// #include "ros/ros.h"
// #include "std_msgs/String.h"
// #include <std_msgs/UInt16.h>
// #include <std_msgs/UInt16MultiArray.h>
// #include <std_msgs/MultiArrayDimension.h>
// #include <sstream>
// #include <iostream>

// using namespace std;

// int cnt = 0;
// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "pub_servomotor_cmd");
//     ros::NodeHandle n;
//     ros::Publisher chatter_pub = n.advertise<std_msgs::UInt16MultiArray>("servomotor_cmd", 1000);
//     ros::Rate loop_rate(1);

//     int motorX = 0;
//     int motorY = 0;

//     while (ros::ok())
//     {
//         std_msgs::UInt16MultiArray servomotor_msg;
//         /* manually input the motor x angle (0~180) */
//         servomotor_msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
//         servomotor_msg.layout.dim[0].size = 2;
//         servomotor_msg.layout.dim[0].stride = 1;
//         servomotor_msg.layout.data_offset = 0;
//         if (cnt > 180)
//         {
//             cnt = 0;
//         }
//         servomotor_msg.data.push_back(cnt);
//         servomotor_msg.data.push_back(180 - cnt);

//         ROS_INFO("data0 = %d", servomotor_msg.data[0]);
//         ROS_INFO("data1 = %d", servomotor_msg.data[1]);
//         ROS_INFO("data2 = %d", servomotor_msg.data[2]);
//         chatter_pub.publish(servomotor_msg);
//         cnt += 5;

//         ros::spinOnce();

//         // ros::spin();

//         loop_rate.sleep();
//     }

//     return 0;
// }

/***************************** do with UInt32  ********************/
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/UInt32.h>
#include <std_msgs/UInt16MultiArray.h>
#include <std_msgs/MultiArrayDimension.h>
#include <sstream>
#include <iostream>

using namespace std;

unsigned long cnt = 0;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "pub_servomotor_cmd");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::UInt32>("servomotor_cmd", 1000);
    ros::Rate loop_rate(1);

    int motorX = 0;
    int motorY = 0;

    while (ros::ok())
    {
        std_msgs::UInt32 servomotor_msg;
        /* manually input the motor x angle (0~180) */
        if (cnt > 180)
        {
            cnt = 0;
        }
        servomotor_msg.data = cnt | ((180-cnt) <<16);

        ROS_INFO("datax = %d", (servomotor_msg.data & 0x0000FFFF));
        ROS_INFO("datay = %d", ((servomotor_msg.data & 0xFFFF0000) >> 16));
        chatter_pub.publish(servomotor_msg);
        cnt += 5;

        ros::spinOnce();

        // ros::spin();

        loop_rate.sleep();
    }

    return 0;
}
