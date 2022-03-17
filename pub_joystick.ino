/* this is the code run on the arduino IDE

   For the full tutorial write up, visit
   https://wiki.ros.org/rosserial_arduino/Tutorials
   https://wiki.ros.org/rosserial_arduino/Tutorials/Push%20Button
   https://answers.ros.org/question/37185/how-to-initialize-a-uint8multiarray-message/

   3 STEPS TO RUN THE CODE:
   1-terminal: roscore
   2-terminal: rosrun rosserial_python serial_node.py /dev/ttyUSB0   -- to startup the node on arduino
   3-terminal: rostopic pub servo std_msgs/UInt16 90   -- to publish the angle
*/

/********************** based on UInt16MultiArray *******************/
//#include <ros.h>
//#include <std_msgs/UInt16.h>
//#include "std_msgs/String.h"
//#include <std_msgs/Bool.h>
//#include <std_msgs/UInt16MultiArray.h>
//#include <std_msgs/MultiArrayDimension.h>
//#include <Servo.h> //accesses the Arduino Servo Library
//ros::NodeHandle  nh;
//
//std_msgs::UInt16MultiArray joydata_msg;
//ros::Publisher pub_joy ("joystick", &joydata_msg);
//
///* std_msgs::Bool pushed_msg; */
///* ros::Publisher pub_button("pushed", &pushed_msg);  */
//
//const int joystickX = 4;
//const int joystickY = 5;
//
//int datax = 0;
//int datay = 0;
//Servo myservo3;  // creates servo object to control a servo
//Servo myservo9;  // creates servo object to control a servo
//
//void setup()
//{
//  nh.initNode();
//  /* motor test */
//  myservo3.attach(3);  // ensures output to servo on pin 3
//  myservo9.attach(9);  // ensures output to servo on pin 9
//
//  joydata_msg.layout.dim = (std_msgs::MultiArrayDimension *)
//                           malloc(sizeof(std_msgs::MultiArrayDimension) * 8);
//  joydata_msg.layout.dim[0].size = 2;
//  joydata_msg.layout.dim[0].stride = 1;
//  joydata_msg.layout.data_offset = 0;
//  joydata_msg.data_length = 4;
//  nh.advertise(pub_joy);
//}
//
//void loop()
//{
//  joydata_msg.data[1] = analogRead(joystickX);
//  joydata_msg.data[2] = analogRead(joystickY);
//
//  /* test on motor */
//  datay = map(joydata_msg.data[1], 0, 1023, 0, 180);     // converts reading from potentiometer to an output value in degrees of rotation that the servo can understand
//  myservo3.write(datay);                  // sets the servo position according to the input from the potentiometer
//  delay(15);
//
//  datax = map(joydata_msg.data[2], 0, 1023, 0, 180);     // converts reading from potentiometer to an output value in degrees of rotation that the servo can understand
//  myservo9.write(datax);                  // sets the servo position according to the input from the potentiometer
//  delay(15);
//  pub_joy.publish(&joydata_msg);
//  nh.spinOnce();
//}
/********************************************************************/

/******************************** based on UInt32 *******************/
#include <ros.h>
#include <std_msgs/UInt16.h>
#include "std_msgs/String.h"
#include <std_msgs/Bool.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/MultiArrayDimension.h>
#include <Servo.h> //accesses the Arduino Servo Library
ros::NodeHandle  nh;

std_msgs::UInt32 joydata_msg;
ros::Publisher pub_joy ("joystick", &joydata_msg);

const int joystickX = 4;
const int joystickY = 5;

int datax = 0;
int datay = 0;
Servo myservo3;  
Servo myservo9;  

void setup()
{
  nh.initNode();
  /* motor test */
  myservo3.attach(3);  // ensures output to servo on pin 3
  myservo9.attach(9);  // ensures output to servo on pin 9

//  joydata_msg.layout.dim = (std_msgs::MultiArrayDimension *)
//                           malloc(sizeof(std_msgs::MultiArrayDimension) * 8);
//  joydata_msg.layout.dim[0].size = 2;
//  joydata_msg.layout.dim[0].stride = 1;
//  joydata_msg.layout.data_offset = 0;
//  joydata_msg.data_length = 4;
  
  nh.advertise(pub_joy);
}

void loop()
{
  joydata_msg.data = ((unsigned long) analogRead(joystickX)) | (((unsigned long) analogRead(joystickY)) << 16);
  /* test on motor */
  datax = map((joydata_msg.data & 0x0000FFFF), 0, 1023, 0, 180);     // converts reading from potentiometer to an output value in degrees of rotation that the servo can understand
  myservo3.write(datax);                  // sets the servo position according to the input from the potentiometer
  delay(15);

  datay = map(((joydata_msg.data & 0xFFFF0000) >> 16), 0, 1023, 0, 180);     // converts reading from potentiometer to an output value in degrees of rotation that the servo can understand
  myservo9.write(datay);                  // sets the servo position according to the input from the potentiometer
  delay(15);
  pub_joy.publish(&joydata_msg);
  nh.spinOnce();
}
