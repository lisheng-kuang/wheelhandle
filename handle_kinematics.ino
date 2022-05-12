/* ref **
   1-trigonometric functions, https://www.arduino.cc/en/math/h
   2-arduino functions, https://www.arduino.cc/reference/en/
   3-return 2 values in a func, https://forum.arduino.cc/t/returning-two-values-from-a-function/90068/5
   4-asin() return one smalles value https://www.arduino.cc/en/Serial/print
 ***/
#include <math.h>

const double RATIO = 10; /* mapp the VR chair to the handle */

const double H = 10;//the height of the platform
//const double PI = 3.1415926;

double pos_z = 0;
double handle_x = 0;
double handle_y = 0;/*the position of the mobile platform, w.r.t the base */

double chair_x = 0; /*position of the chair */
double chair_y = 0;

struct values {
  double axis_x;
  double axis_y;
};
struct values handle_pos;

void setup ()
{

}
void loop()
{
  handle_pos = position_mapping(chair_x, chair_y);
  /* test */
  pos_z = inverse_kinematics(handle_pos.axis_x, handle_pos.axis_y);
}


/* mapp the position of the VR chair into the handle */
struct values position_mapping(double x, double y)
{
  struct values output_pos;

  output_pos.axis_x = RATIO * x;
  output_pos.axis_y = RATIO * y;

  return output_pos;
}
/* test */


//pos_x = handle_pos.axis_x;
/* inverse kinematics, given the position of the platform,
   derive the angle of the two motors */
/* pos_x pos_y is the position of the mobile platform */
double inverse_kinematics(double pos_x, double pos_y)
{
  pos_z = sqrt(sq(H) - sq(pos_x) - sq(pos_y));
  /* pos_x =0, pos_y > 0  */

}

/* return the position cmd for the motors */
struct values inverse_kinematics(values pos)
{
  double pos_x = 0;
  double pos_y = 0;
  struct values angle;
  double angle_x = 0; //rad
  double angle_y = 0;
  double theta = 0;
  double gama = 0;

  pos_z = sqrt(sq(H) - sq(pos.axis_x) - sq(pos.axis_y));
  pos_z = abs(pos_z);

  /* start checking the values of the two axis */
  if ((pos.axis_x = 0) && (pos.axis_y > 0))
  {
    theta = 2.0d * acos((double)(pos.axis_y / H)); //acos return rad, 1 rad = 57.29578 degree
    angle.axis_x = atan((double) 2.0d / tan(theta / 2.0d));
    angle.axis_y = angle_x;  // rad
    // to continue range
  }
  if ((pos.axis_x = 0) && (pos.axis_y < 0))
  {
    theta = 2.0d * acos((double)(- pos.axis_y / H));
    angle.axis_x = atan((double) (- 2.0d / tan(theta / 2.0d)));
    angle.axis_y = angle_x;  // rad
    // to continue range
  }
  if ((pos.axis_x > 0) && (pos.axis_y = 0))
  {
    theta = 2.0d * acos((double)(pos.axis_x / H));
    angle.axis_x = atan((double)((sq(3) / 2.0d) / tan(theta / 2.0d)));
    angle.axis_y = atan((double)(-(sq(3) / 2.0d) / tan(theta / 2.0d)));
    // to continue range
  }
  if ((pos.axis_x < 0) && (pos.axis_y = 0))
  {
    theta = 2.0d * acos((double)(- pos.axis_x / H));
    angle.axis_x = atan((double)(- (sq(3) / 2.0d) / tan(theta / 2.0d)));
    angle.axis_y = atan((double)( (sq(3) / 2.0d) / tan(theta / 2.0d)));
    // to continue range
  }

  if ((pos.axis_x > 0) && (pos.axis_y > 0))
  {
    /* 0<game<PI/2 */
    gama = atan(pos.axis_y / pos.axis_x);
    theta = 2.0d * asin(pos_z / H);
    angle.axis_x = atan(1.0d / (tan(theta / 2.0d) * sin(gama + PI / 3.0d)));
    angle.axis_y = atan(1.0d / (tan(theta / 2.0d) * sin(gama - PI / 3.0d)));
    // to continue range
  }
  if ((pos.axis_x < 0) && (pos.axis_y > 0))
  {
    /* PI/2<game<PI */
    gama = atan(pos.axis_y / pos.axis_x);
    gama += PI;
    theta = 2.0d * asin(pos_z / H);
    angle.axis_x = atan(1.0d / (tan(theta / 2.0d) * sin(gama + PI / 3.0d)));
    angle.axis_y = atan(1.0d / (tan(theta / 2.0d) * sin(gama - PI / 3.0d)));
    // to continue range
  }

  if ((pos.axis_x < 0) && (pos.axis_y < 0))
  {
    /* PI<game<3*PI/2 */
    gama = atan(pos.axis_y / pos.axis_x);
    gama += PI;
    theta = 2.0d * asin(pos_z / H);
    angle.axis_x = atan(1.0d / (tan(theta / 2.0d) * sin(gama + PI / 3.0d)));
    angle.axis_y = atan(1.0d / (tan(theta / 2.0d) * sin(gama - PI / 3.0d)));
    // to continue range
  }
  if ((pos.axis_x > 0) && (pos.axis_y < 0))
  {
    /* 3*PI/2<game<2*PI */
    gama = atan(pos.axis_y / pos.axis_x);
    gama += 2.0 * PI;
    theta = 2.0d * asin(pos_z / H);
    angle.axis_x = atan(1.0d / (tan(theta / 2.0d) * sin(gama + PI / 3.0d)));
    angle.axis_y = atan(1.0d / (tan(theta / 2.0d) * sin(gama - PI / 3.0d)));
    // to continue range
  }
  return angle;
}

int serv_motor_x = 0;
int serv_motor_y = 0;
int serv_motor_x_current = 90;// depends on the motor position
int serv_motor_y_current = 90;
void set_motor(values angle)
{
  int motor_pos_x = 0;
  int motor_pos_y = 0;
  int motor_diff_x = 0;
  int motor_diff_y = 0;
  motor_pos_x = angle.axis_x * 57.29578 + 90;
  motor_pos_y = angle.axis_y * 57.29578 + 90;
  motor_diff_x = abs(motor_pos_x - serv_motor_x_current);
  motor_diff_y = abs(motor_pos_y - serv_motor_y_current);
  serv_motor_x_current = angle.axis_x * 57.29578;
  serv_motor_y_current = angle.axis_y;

}
