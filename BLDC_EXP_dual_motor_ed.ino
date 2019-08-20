#include<Servo.h>
#define MOTOR_PIN1			9
#define MOTOR_PIN2      10
#define MOTOR_MAX_SPEED		 2000
#define MOTOR_START_SPEED  1000
#define MAX_SIGNAL 2000
#define MIN_SIGNAL 900
int motor_current_speed = 0;
int i = 0;
int old_speed = 0;
int new_speed = 0;

Servo motor1,motor2;
void motorSetSpeed(int SPEED)
{
  // Don't let the motor go above or below pre-determined max and min
  if (SPEED >= MOTOR_MAX_SPEED)
    SPEED = MOTOR_MAX_SPEED;
  else if (SPEED <= MOTOR_START_SPEED)
    SPEED = MOTOR_START_SPEED;

  motor1.writeMicroseconds(SPEED);
motor2.writeMicroseconds(SPEED);
  motor_current_speed = SPEED;
  //Serial.print("current motor speed = ");
 // Serial.println(motor_current_speed);
}
void esc_calib()
{
  //ESC Calibration*************************************
  Serial.println("Turn on power source, wait for 1st Beep, then within 2 seconds , press any key and enter.");
  Serial.println("ESC Calibration started....");
  Serial.println("Sending MAX_SIGNAL");
  motor1.writeMicroseconds(MAX_SIGNAL);
  motor2.writeMicroseconds(MAX_SIGNAL); // Wait for input
  while (!Serial.available());
  Serial.read();
  // Send min output
  Serial.println("Sending MIN_SIGNAL");
  motor1.writeMicroseconds(MIN_SIGNAL);
  motor2.writeMicroseconds(MIN_SIGNAL);
  Serial.println("....ESC Calibration Complete");
  //*****************************************************
}
void setup()
{
  Serial.begin(9600);
  motor1.attach(MOTOR_PIN1);
 motor2.attach(MOTOR_PIN2); 
  esc_calib(); 
  old_speed = MOTOR_START_SPEED;
}


void loop()
{
 
 Serial.println("Enter the new speed");
  // Wait for input
  while (!Serial.available());     
    new_speed = Serial.parseInt();
    Serial.println(new_speed);
    Serial.flush();
   // char buffer[]={' ',' ',' ',' ',};
 // while(!Serial.available());
  //Serial.readBytesUntil('n',buffer,4);
  //int incomingValue =atoi(buffer);
 // Serial.println(incomingValue);
 // new_speed = incomingValue;
    
  if (new_speed > old_speed)
  {
    Serial.println("Loop1");
    for (i = old_speed; i <= new_speed; i = i + 3)
    {
      motorSetSpeed(i);
    }
      old_speed = new_speed;
    
  }
 else if (new_speed <old_speed) 
  {
    Serial.println("Loop2");
    for (i = old_speed; i >= new_speed; i = i - 3)
    {
      motorSetSpeed(i);
    }
    old_speed = new_speed;
  }





}
