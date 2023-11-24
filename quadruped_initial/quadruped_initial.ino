#include <math.h>
#include <Servo.h>
//setting servo pins and object
const int servo_pin[4][3] = {{13,2,3},{4,5,6},{7,8,9},{10,11,12}};
//servo pinsa are in the order {tibia,femur,pivot}  {L,R,L,R}  30 :{ restrict,extends,restrics,extends}

double calc_angles[3];
Servo servo[4][3];


//measurements in millimeters
const double tibia_length = 77.1;
const double femur_length = 50;       
const double pivot_length = 27.5;

//set resting heights
const int z = 15;

void setup() {
  //first let us setup the servos
 // servo_setup();
  Serial.begin(9600);

  
}

void loop() {
  for(int i = 0;i<3;i++)
  {
    Serial.println(calc_angles[0]);
  }
}
//requires additional powersupply
//causes robot to bug out only on PC power
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

void ik_angles(double posx,double posy, double posz)
{
  double l = sqrt(posx*posx+posy*posy)-pivot_lenngth;
  calc_angles[0] =  acos((pow(tibia_length,2.0)+pow(femur_length,2.0)-pow(l,2.0))/(2*tibia_length*femur_length));
  calc_angles[1] = acos((pow(femur_legnth,2.0)+pow(l,2.0)-pow(tibia_length,2.0))/(2*l*femur_length))+atan(l/posz);
  calc_angles[2] = atan(posy/posx);
  toDegree();

}
void toDegree()
{
  calc_angles[0] = RAD_TO_DEG*calc_angles[0];
  calc_angles[1] = RAD_TO_DEG*calc_angles[1];
  calc_angles[2] = RAD_TO_DEG*calc_angles[2];
}


