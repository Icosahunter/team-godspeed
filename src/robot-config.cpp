#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision20__BLUE_BALL = signature (1, -3189, -2341, -2765, 7617, 14309, 10963, 2.5, 0);
signature Vision20__RED_BALL = signature (2, 5065, 8971, 7018, -891, 1, -445, 2.5, 0);
signature Vision20__BACKBOARD = signature (3, -4887, -4045, -4466, -5461, -4157, -4809, 2.4, 0);
signature Vision20__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision20 = vision (PORT20, 90, Vision20__BLUE_BALL, Vision20__RED_BALL, Vision20__BACKBOARD, Vision20__SIG_4);
/*vex-vision-config:end*/
bumper BumperA = bumper(Brain.ThreeWirePort.A);
bumper BumperB = bumper(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);
motor FrontRightMotor = motor(PORT1, ratio18_1, false);
motor FrontLeftMotor = motor(PORT2, ratio18_1, false);
motor BackMotor = motor(PORT3, ratio18_1, false);
motor LeftCollectorMotor = motor(PORT4, ratio6_1, false);
motor RightCollectorMotor = motor(PORT5, ratio6_1, true);
motor ScorerMotor = motor(PORT7, ratio18_1, false);
motor ballGuideMotor = motor(PORT8, ratio18_1, false);
sonar RangeFinder1 = sonar(Brain.ThreeWirePort.C);

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