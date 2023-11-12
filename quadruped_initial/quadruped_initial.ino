
#include <Servo.h>
//setting servo pins and object
const int servo_pin[4][3] = {{13,2,3},{4,5,6},{7,8,9},{10,11,12}};
//servo pinsa are in the order {tibia,femur,pivot}  {L,R,L,R}  30 :{ restrict,extends,restrics,extends}
Servo servo[4][3];


//measurements in millimeters
const int tibia_length = 77.1;
const int femur_length = 50;
const int pivot_length = 27.5;

//set resting heights
const int z = 10;

void setup() {
  //first let us setup the servos
 // servo_setup();
 servo[1][0].attach(servo_pin[3][0]);

}

void loop() {
  //let us first make it stand
  //for(int i = 30;i<=120;i++)
  //{servo[0][0].write(i);delay(10);}
  
  for(int i = 30;i<150;i++)
  {
  servo[1][0].write(i);delay(10);
  }
  for(int i = 150;i>30;i--)
  {
  servo[1][0].write(i);delay(10);
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

