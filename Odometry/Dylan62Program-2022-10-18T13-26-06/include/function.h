#include "robot-config.h"
#include "vex.h"

//a function that can be used to move all of the motors at once
void moveAll(double power){
    leftMotor1.spin(forward,power,pct);
    //leftMotor2.spin(forward,power,pct);
    //leftMotor3.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    //rightMotor2.spin(forward,power,pct);
    //rightMotor3.spin(forward,power,pct);

}

//useful for debugging, this function will print any relevant values as needed
void exitAutonInformation(double error, double derivative){
    Brain.Screen.print(error);
    Brain.Screen.print(" ");
    Brain.Screen.print(derivative);
    Brain.Screen.newLine();
    Brain.Screen.print("Leaving Auton");
}

//returns the average of all the motors sensor values
double getSensorValue(){
  double sensorValueLeft,sensorValueRight,sensorValueTotal;
  sensorValueLeft = leftMotor1.position(degrees);
  sensorValueRight = rightMotor1.position(degrees);
  sensorValueTotal = sensorValueLeft + sensorValueRight / 2;
  return sensorValueTotal;
}

//for when we get more motors
double getSensorValueLeft() {
  return leftMotor1.position(degrees);
}

//for when we get more motors
double getSensorValueRight() {
  return rightMotor1.position(degrees);
}

//the pd loop for the robot, when given a specific distance the robot will travel that amount of distance. The setpoint is in
//degrees of the wheel. if the robot overshoots, it will return backwards slightly. already mostly tuned but will need to be refined to the final robot
void PDLoop(double setpoint, bool isTurning = false){
  //setpoint : the amount of rotations that we aim to move in degrees
  //derivative : holds the current amount of the derivative
  //prevError : holds the pervious error for calculation in the next cycle
  //power : holds the amount of power to give to the motor
  //error : hold the amount of distance left to go
  //kp : The kP value is used to tune our Porportional part of the PD controller
  //kD : the kD value is used to tune our Derivative part of the PD controller

  double derivative, prevError = 0;
  double power = 0, error = setpoint;
  double kP = 0.2485, kD = 0.119;

  //reset the position of the motors to make sure the distance is correct
  leftMotor1.setPosition(0,degrees);
  rightMotor1.setPosition(0,degrees);

  //the loop that calculates how much further to go and then gives the motors an appropriate amount of power
  while (fabs(error) >= 1.0 && !isTurning)
  {
    //wheel diameter 3.25, circumference 10.21017612416682802499 or 3.25 * pi
    //0.02836160034490785562 per degree

    //calculate the error by subtracting how far the robot has moved from how far it needs to go
    error = setpoint - getSensorValue();
    
    //calculate the derivative by subtrating our last error from our new current error
    derivative = error - prevError;
    prevError = error;

    //set the amount of power for the robot
    power = error * kP + derivative * kD;
    
    //spin the wheels based off the power we calculated
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    wait(20,msec);
  }

  //the only difference in this loop is if it is turning, one of the motors is in reverse instead
  while (fabs(error) >= 1.0 && isTurning) 
  {
    error = setpoint - getSensorValue();
    
    derivative = error - prevError;
    prevError = error;

    power = error * kP + derivative * kD;
    
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(reverse,power,pct);
    wait(20,msec);
  }

  //in case the motors still have a small amount of power after exiting the auton loop,
  //these loops will slowly power the motors down before exiting at 0 power, in the way needed for turning on not
  
  if (fabs(power) > 0) {
    power = power / 2;
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    wait(30,msec);
    power = 0;
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
  }
  
  exitAutonInformation(error, derivative);
}

//current function for turning the robot, converts the degrees given to inches required and sends it to the PDLoop
void turnRobot(double setDegrees)
{
  double requiredDistance, rotationDegree;

  //this calculates how many inches is required to be moved each degree
  //track width * pi / total degrees in one rotation = 0.0575958653
  rotationDegree = 6.6 * 3.14159265358979323846 / 360;

  //this converts the degrees given into an amount of rotations that can be used for the PDLoop
  //rotation degree above * how many degrees we wish to move / 2? / inches per degree = amount of degrees to move the robot
  requiredDistance = rotationDegree * setDegrees / 2 / 0.02836160034490785562;
  
  PDLoop(requiredDistance, true);
}