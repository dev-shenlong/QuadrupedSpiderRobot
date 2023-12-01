#include <math.h>
#include <Servo.h>
//setting servo pins and object
const int servo_pin[4][3] = {{13,2,3},{4,5,6},{7,8,9},{10,11,12}};
//servo pinsa are in the order {tibia,femur,pivot}  {L,R,L,R}  30 :{ restrict,extends,restrics,extends}

double calc_angles[3];
Servo servo[4][3];


//measurements in millimeters
const double tibia_length = 80;
const double femur_length = 50;       
const double pivot_length = 27.5;

//set resting heights
const int z = 45;

//array to maintain current positons
int x = 60;
int y = 60;
int leg_pos[4][3] = {{0,sqrt(y*x*2),z+20},{x,y,z},{0,sqrt(x*y*2),z},{x,y,z+15}};
//array to maintain servo angles
float curr_angle[4][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

void setup() {
  //first let us setup the servos
 //servo[0][0].attach(servo_pin[3][0]);
  servo_setup();
  
  Serial.begin(9600);//for debugging
  for(int i = 0;i<z;i++)
  {
    initialize_start(i);
  }
  
}

void loop() 
{
  
 

}

//attach all servos
void servo_setup()
{
  for(int i = 0;i<4;i++)
  {
    for(int j = 0;j<3;j++)
    {
      servo[i][j].attach(servo_pin[i][j]);
      
    }
  }
}

//to make the robot stand up
void initialize_start(int z)
{
  //for leg in 1 position
  ik_angles(0,sqrt(x*x+y*y),z+20);
   calc_angles[1] = 180 - calc_angles[1];
  drive_servo(servo[0][0],90,calc_angles[0]);
  drive_servo(servo[0][1],90,calc_angles[1]);
  drive_servo(servo[0][2],90,calc_angles[2]);
  setAngle(0,calc_angles);
  
  //for leg in 2 position
  ik_angles(x,y,z);
  calc_angles[0] = 180 - calc_angles[0];
  calc_angles[2] = 180 - calc_angles[2];
  drive_servo(servo[1][0],90,calc_angles[0]);
  drive_servo(servo[1][1],90,calc_angles[1]);
  drive_servo(servo[1][2],90,calc_angles[2]);
  setAngle(1,calc_angles);
   //for leg in 3 position
   delay(100);
  ik_angles(0,sqrt(x*x+y*y),z);
   calc_angles[1] = 180 - calc_angles[1];
  drive_servo(servo[2][0],90,calc_angles[0]);
  drive_servo(servo[2][1],90,calc_angles[1]);
  drive_servo(servo[2][2],90,calc_angles[2]);
  setAngle(2,calc_angles);
     //for leg in 4 position
  ik_angles(-x,y,z+15);
  calc_angles[0] = 180 - calc_angles[0];
  calc_angles[2] = 180 - calc_angles[2];
  drive_servo(servo[3][0],90,calc_angles[0]);
  drive_servo(servo[3][1],90,calc_angles[1]);
  drive_servo(servo[3][2],90,calc_angles[2]);
  setAngle(3,calc_angles);
  
  
}

void drive_servo(Servo target_servo,float start_angle,float end_angle)
{
  //will turn servo in parts of 20 ms change delay to change speed of servo
  int time_interval = 100;
  int direction = abs(end_angle-start_angle)/(end_angle-start_angle);
  float i,j;
  if(direction<0)
  {
    i = start_angle;
    j = end_angle;
  }
  else
  {
    i = end_angle;
    j = start_angle;
  }
  for(;i<j;i+=direction)
  {
  
    delay(time_interval);
  }
  target_servo.write(end_angle);
}
//Calculations
void ik_angles(double posx,double posy, double posz)
{
  double l = sqrt(posx*posx+posy*posy)-pivot_length;
  calc_angles[0] =  acos((pow(tibia_length,2.0)+pow(femur_length,2.0)-pow(l,2.0))/(2*tibia_length*femur_length));
  calc_angles[1] = acos((pow(femur_length,2.0)+pow(l,2.0)-pow(tibia_length,2.0))/(2*l*femur_length))+atan(l/posz);
  calc_angles[2] = atan(posy/posx);
  toDegree();
  if(calc_angles[2]<0)
  {
    calc_angles[2] += 180;
  }

}
void toDegree()
{
  calc_angles[0] = RAD_TO_DEG*calc_angles[0];
  calc_angles[1] = RAD_TO_DEG*calc_angles[1];
  calc_angles[2] = RAD_TO_DEG*calc_angles[2];
}

void setAngle(int index, float angles[])
{
  curr_angle[index][0] = angles[0];
  curr_angle[index][1] = angles[1];
  curr_angle[index][2] = angles[2]];
}
void move_leg_with_lifting(int leg_no,int desired_pos[])
{
}
void move_leg_without_lifting(int leg_no, int desired_pos[])
{
}