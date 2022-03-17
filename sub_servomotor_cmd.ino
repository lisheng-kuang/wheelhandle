/* this is the code run on the arduino IDE
   rosserial Servo Control Example

   This sketch demonstrates the control of hobby R/C servos
   using ROS and the arduiono

   For the full tutorial write up, visit
   www.ros.org/wiki/rosserial_arduino_demos

   For more information on the Arduino Servo Library
   Checkout :
   http://www.arduino.cc/en/Reference/Servo
   rostopic pub servo std_msgs/UInt16  <angle>
   REF: https://www.youtube.com/watch?v=cui0I4HAmwM
   3 STEPS TO RUN THE CODE:
   1-terminal: roscore
   2-terminal: rosrun rosserial_python serial_node.py /dev/ttyUSB0   -- to startup the node on arduino
   3-terminal: rostopic pub servo std_msgs/UInt16 90   -- to publish the angle
*/
/*********************** for UInt16MultiArray ********************/
//#if defined(ARDUINO) && ARDUINO >= 100
//#include "Arduino.h"
//#else
//#include <WProgram.h>
//#endif
//#include <ros.h>
//#include <std_msgs/UInt16.h>
//#include "std_msgs/String.h"
//#include <std_msgs/UInt16MultiArray.h>
//#include <std_msgs/MultiArrayDimension.h>
//#include <Servo.h>
//
//
//ros::NodeHandle  nh;
//
//Servo myservo3;
//Servo myservo9;
//
//void servo_cb( const std_msgs::UInt16MultiArray& servomotor_msg)
//{
//  //set servo angle, should be from 0-180
//  myservo3.write(servomotor_msg.data[0]);
//  myservo9.write(servomotor_msg.data[1]);
//  delay(15);
//}
//// servomotor_cmd is the topic from the publisher 
//ros::Subscriber<std_msgs::UInt16MultiArray> servomotor_cmd("servomotor_cmd", servo_cb);
//
//void setup()
//{
//  nh.initNode();
//  nh.subscribe(servomotor_cmd);
//
//  myservo3.attach(3); //attach it to pin 3
//  myservo9.attach(9); //attach it to pin 9
//}
//
//void loop() {
//  nh.spinOnce();
//  delay(1);
//}

/*********************** for UInt32 ********************/
#include <ros.h>
#include <std_msgs/UInt32.h>
#include <Servo.h>

ros::NodeHandle  nh;

Servo myservo3;
Servo myservo9;

void servo_cb( const std_msgs::UInt32& servomotor_msg)
{
  //set servo angle, should be from 0-180
  myservo3.write(servomotor_msg.data & 0x0000FFFF);
  myservo9.write((servomotor_msg.data & 0xFFFF0000) >> 16);
  delay(15);
}
// servomotor_cmd is the topic from the publisher 
ros::Subscriber<std_msgs::UInt32> servomotor_cmd("servomotor_cmd", servo_cb);

void setup()
{
  nh.initNode();
  nh.subscribe(servomotor_cmd);

  myservo3.attach(3); //attach it to pin 3
  myservo9.attach(9); //attach it to pin 9
}

void loop() {
  nh.spinOnce();
  delay(1);
}

