/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightMiddle          motor         9               
// rightFront           motor         10              
// rightRear            motor         8               
// leftFront            motor         1               
// leftMiddle           motor         2               
// leftRear             motor         3               
// Controller1          controller                    
// Catapult             motor         21              
// cataLimit            limit         A               
// liftPistons          digital_out   F               
// intakePistons        digital_out   C               
// Intake               motor         5               
// rightRaised          motor         6               
// leftRaised           motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "MotorFunctions.cpp"
#include "math.h"
#include <iostream>
using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;


bool pidState = true;
int r1 = 0;
int LP = 0;
int IP = 0;
int intakeStatus = 0;

bool liftCheck = false;
bool intakeCheck = false;
bool intakeMotor = false;
//int cataPosition = 0;




//lift position Toggle
/*void setLP(){
  if (LP==1){
    LP=0;
    cout<<"LP = 0"<<endl;
    }
 else if (LP==0){
   LP=1;
   cout<<"LPL=1"<<endl;
 }
}*/

void setR1(){
  r1 = 1;
}
//this is how you push things


void setLiftCheck(){
  liftCheck = true;
}

void setIntakeCheck(){
  intakeCheck=true;
}

void setIntakeMotor(){
  intakeMotor = true;
}
//intake postion toggle


  //Intake Status Toggle
  void setIntakeStatus (){
      intakeMotor = true;
    }
  

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


  

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
    encoderReset();
    while (pidState){
      pidCalcLBank(10,0,0,32);
      pidCalcRBank(10,0,0,3);
      mBLeft();
      mBRight();
      if(targetR >= errorR){
        pidState=false;
      }
      else{
      // When we call these functions separately we run into the issue of how far each wheel
      // wants to move before we get to the next function therefore we need to figure out how
      // to call them at the same time. This is the reason it turned to the right before the
      // right started moving
     /*mBLeft();
     mBRight();

     pidCalcAll(12,.005,20,4);
     mAll();*/
      wait (5, msec);
      }
    }

    std::cout<< "Exited PID"<<std::endl;
   //ait (1000, msec);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
  Controller1.ButtonL1.pressed(setLiftCheck);  
  Controller1.ButtonR1.pressed(setR1);
  cataPosition = cataLimit.pressing();
  Controller1.ButtonL2.pressed(setIntakeCheck);
  Controller1.ButtonA.pressed(setIntakeStatus);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    
    //Catapult.spin(forward,100, pct);

  if (liftCheck){
      if (LP==1){
        LP=0;
        liftCheck=false;
      }
      else if (LP==0 && liftCheck){
          LP=1;
          liftCheck=false;
      }
  }
  
    if (intakeCheck){
      if (IP==1){
        IP=0;
        intakeCheck=false;
      }
      else if (IP==0 && intakeCheck){
          IP=1;
          intakeCheck=false;
      }
  }


 if (intakeMotor){
      if (intakeStatus==1){
        intakeStatus=0;
        intakeMotor=false;
      }
      else if (intakeStatus==0 && intakeMotor){
          intakeStatus=1;
          intakeMotor=false;
      }
  }
// Catapult Launch Position
    if (r1 == 1){
      if(cataPosition !=1 ){
         Catapult.spin(fwd,60,pct);
      }
      else{
        Catapult.stop(coast);
        r1 = 0;
      }
    }

//Fire Catapult
   if (Controller1.ButtonY.pressing()){
      Catapult.spinFor(fwd,80,deg);
      r1=1;
      }


//intake

/*
if (intakeStatus == 1){
    Intake.spin(fwd,100,pct);
}
else if (intakeStatus ==0){
  Intake.stop(coast);
}
*/

if(Controller1.ButtonR1.pressing()){
  Intake.spin(fwd, 100, pct);
}else if(Controller1.ButtonR2.pressing()){
  Intake.spin(reverse, 100, pct);
}else
  Intake.stop(brakeType::brake);
//tank drive

  //left Motors
  leftFront.spin(fwd,(Controller1.Axis3.position(pct)),pct);
  leftMiddle.spin(fwd,(Controller1.Axis3.position(pct)),pct);
  leftRear.spin(fwd,(Controller1.Axis3.position(pct)),pct);
  leftRaised.spin(fwd,(Controller1.Axis3.position(pct)),pct);

  //right Motors
  rightFront.spin(fwd,(Controller1.Axis2.position(pct)),pct);
  rightMiddle.spin(fwd,(Controller1.Axis2.position(pct)),pct);
  rightRear.spin(fwd,(Controller1.Axis2.position(pct)),pct);
  rightRaised.spin(fwd,(Controller1.Axis2.position(pct)),pct);


    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    liftPistons.set(LP);
    intakePistons.set(IP);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
