
/**************************** do with  UInt16MultiArray ********************/
// #include <stdlib.h>
// #include <iostream>
// #include "ros/ros.h"
// #include "std_msgs/String.h"

// #include <std_msgs/MultiArrayDimension.h>
// #include <std_msgs/UInt16MultiArray.h>
// /* ref: https://gist.github.com/jarvisschultz/7a886ed2714fac9f5226 */
// /* this is for the sub to receive data from the joystick module */
// /* not the real joystick module */

// /* header files for maestroboard command port */
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <termios.h>
// #include <string.h>
// #define Sleep(x) usleep((x)*1000 * 1000) // x ==1, for 1 second

// int joystickX = 0;
// int joystickY = 0;
// void subCallback(const std_msgs::UInt16MultiArray::ConstPtr &joydata_msg)
// {
//     /* joydata_msg->data[1] for x axis, joydata_msg->data[2] for y axis */
//     joystickX = joydata_msg->data[0 + 1];
//     joystickY = joydata_msg->data[0 + 2];
//     ROS_INFO("joystickX = %d", joydata_msg->data[0 + 1]);
//     ROS_INFO("joystickY = %d", joydata_msg->data[0 + 2]);
// }
// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "Subscriber");
//     ros::NodeHandle n;
//     /* joystick published topic from the joystick */
//     ros::Subscriber sub = n.subscribe("joystick", 1000, subCallback);
//     // ros::spin();

//     while (ros::ok())
//     {
//         bool success = 0;

//         ROS_INFO("joystick axis data is joystickX = %d, joystickY = %d", joystickX, joystickY);
//         // ROS_INFO("Waiting for command ~v~. \n");

//         ros::spin();
//         Sleep(0.1);
//     }
// }

/**************************** do with  UInt32 ********************/
#include <stdlib.h>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/UInt32.h>
/* ref: https://gist.github.com/jarvisschultz/7a886ed2714fac9f5226 */
/* this is for the sub to receive data from the joystick module */
/* not the real joystick module */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#define Sleep(x) usleep((x)*1000 * 1000) // x ==1, for 1 second

int joystickX = 0;
int joystickY = 0;
void subCallback(const std_msgs::UInt32::ConstPtr &joydata_msg)
{
    joystickX = (joydata_msg->data & 0x0000FFFF);
    joystickY = (joydata_msg->data & 0xFFFF0000) >> 16;
    ROS_INFO("joystickX = %d", joystickX);
    ROS_INFO("joystickY = %d", joystickY);
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "Subscriber");
    ros::NodeHandle n;
    /* joystick published topic from the joystick */
    ros::Subscriber sub = n.subscribe("joystick", 1000, subCallback);
    // ros::spin();

    while (ros::ok())
    {
        bool success = 0;

        ROS_INFO("joystick axis data is joystickX = %d, joystickY = %d", joystickX, joystickY);
        // ROS_INFO("Waiting for command ~v~. \n");

        ros::spin();
        Sleep(0.1);
    }
}
