using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor lMotor1;
extern motor lMotor2;
extern motor lMotor3;
extern motor lMotor4;
extern motor rMotor1;
extern motor rMotor2;
extern motor rMotor3;
extern motor rMotor4;
extern motor cataMotor;
extern motor intakeRollerMotor;
extern digital_out endGame;
extern controller Controller1;
extern digital_out autonPiston;
extern limit cataLimit;
extern optical OpticalRight;
extern optical OpticalLeft;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );