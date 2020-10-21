#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision1__BLUE_BALL = signature (1, -3189, -2341, -2765, 7617, 14309, 10963, 2.5, 0);
signature Vision1__RED_BALL = signature (2, 5065, 8971, 7018, -891, 1, -445, 2.5, 0);
signature Vision1__BACKBOARD = signature (3, -4887, -4045, -4466, -5461, -4157, -4809, 2.4, 0);
signature Vision1__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision1 = vision (PORT1, 90, Vision1__BLUE_BALL, Vision1__RED_BALL, Vision1__BACKBOARD, Vision1__SIG_4);
/*vex-vision-config:end*/
bumper BumperA = bumper(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}