#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision20__RED_BALL = signature (1, 5097, 7215, 6156, -235, 493, 129, 2.6, 0);
signature Vision20__BLUE_BALL = signature (2, -2115, -1413, -1764, 6175, 7889, 7032, 5, 0);
signature Vision20__BACKBOARD = signature (3, -5881, -5085, -5483, -6089, -5461, -5775, 11, 0);
vision Vision20 = vision (PORT19, 50, Vision20__RED_BALL, Vision20__BLUE_BALL, Vision20__BACKBOARD);
/*vex-vision-config:end*/
bumper BumperA = bumper(Brain.ThreeWirePort.A);
bumper BumperB = bumper(Brain.ThreeWirePort.B);
controller Controller1 = controller(primary);
motor FrontRightMotor = motor(PORT1, ratio36_1, false);
motor FrontLeftMotor = motor(PORT2, ratio36_1, false);
motor BackMotor = motor(PORT3, ratio36_1, false);
motor LeftCollectorMotor = motor(PORT4, ratio18_1, false);
motor RightCollectorMotor = motor(PORT5, ratio18_1, true);
motor ScorerMotor = motor(PORT17, ratio18_1, false);
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