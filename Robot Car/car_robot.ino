#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

Servo servo_motor;

//sensor pins
const int trigPin = A5;
const int echoPin = A3;

#define maximum_distance 400
boolean goesForward = false;
int distance = 100;

const int carSpeed = 200;
const int safetyDistance = 10;

NewPing sonar(trigPin, echoPin, maximum_distance); //sensor function

void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(carSpeed);
  motor2.setSpeed(carSpeed);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);

  servo_motor.attach(9);
}

void loop() {

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= safetyDistance)
  {
    Serial.println("backward");
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft)
    {
      turnRight();
      moveStop();
    }
    else
    {
      turnLeft();
      moveStop();
    }
  }
  else
  {
    Serial.println("forward");
    moveForward(); 
  }
    distance = readPing();
}

int lookRight()
{  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
 delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft()
{
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing()
{
  delay(70);
  
  int cm = sonar.ping_cm();
  
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void moveStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  motor1.run(BRAKE);
  motor2.run(BRAKE);
}

void moveForward()
{

  if(!goesForward)
  {
     
    goesForward=true;

    motor1.run(RELEASE);
    motor2.run(RELEASE);
  
    delay(500);   
    
     motor1.run(FORWARD);
     motor2.run(FORWARD);
  }
}
//
void moveBackward()
{

  goesForward=false;

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  delay(500);
  
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  
}

void turnRight()
{

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  delay(500);
  
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  
  delay(500);
  
//  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  delay(500);
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void turnLeft(){

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  
  delay(500);
  
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  
  delay(500);
  
  motor1.run(RELEASE);
//  motor2.run(RELEASE);
  
  delay(500);
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
