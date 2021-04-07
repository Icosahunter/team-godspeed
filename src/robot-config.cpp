#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision20__RED_BALL = signature (1, 6225, 8395, 7310, -559, 187, -186, 2.2, 0);
signature Vision20__BLUE_BALL = signature (2, -3093, -2323, -2708, 11031, 13237, 12134, 2.5, 0);
signature Vision20__BACKBOARD = signature (3, -4877, -4487, -4682, -5125, -4575, -4850, 2.5, 0);
vision Vision20 = vision (PORT20, 50, Vision20__RED_BALL, Vision20__BLUE_BALL, Vision20__BACKBOARD);
/*vex-vision-config:end*/
bumper BumperA = bumper(Brain.ThreeWirePort.A);
bumper BumperB = bumper(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);
motor FrontRightMotor = motor(PORT1, ratio36_1, false);
motor FrontLeftMotor = motor(PORT2, ratio36_1, false);
motor BackMotor = motor(PORT3, ratio36_1, false);
motor LeftCollectorMotor = motor(PORT4, ratio18_1, false);
motor RightCollectorMotor = motor(PORT5, ratio18_1, true);
motor ScorerMotor = motor(PORT7, ratio18_1, false);
motor LeftBallGuideMotor = motor(PORT8, ratio18_1, false);
motor RightBallGuideMotor = motor(PORT9, ratio18_1, true);
sonar LeftRangeFinder = sonar(Brain.ThreeWirePort.E);
sonar RightRangeFinder = sonar(Brain.ThreeWirePort.C);

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