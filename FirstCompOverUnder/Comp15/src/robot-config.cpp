#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor lMotor1 = motor(PORT11, ratio6_1, true);
motor lMotor2 = motor(PORT12, ratio6_1, true);
motor lMotor3 = motor(PORT13, ratio6_1, true);
motor rMotor1 = motor(PORT18, ratio6_1, false);
motor rMotor2 = motor(PORT19, ratio6_1, false);
motor rMotor3 = motor(PORT17, ratio6_1, false);
motor cataMotor = motor(PORT5, ratio36_1, false);
motor intakeRollerMotor = motor(PORT10, ratio18_1, false);
controller Controller1 = controller(primary);
limit cataLimit = limit(Brain.ThreeWirePort.A);
digital_out intakeFlip = digital_out(Brain.ThreeWirePort.F);
digital_out wings = digital_out(Brain.ThreeWirePort.C);
motor rMotor4 = motor(PORT20, ratio18_1, false);
motor lMotor4 = motor(PORT14, ratio18_1, true);
digital_out endgame = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}