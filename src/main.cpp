/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\anzel                                            */
/*    Created:      Tue Sep 29 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision1              vision        1               
// BumperA              bumper        A               
// Controller1          controller                    
// Motor1               motor         4               
// Motor2               motor         7               
// Motor3               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

/** \namespace godspeed
* \brief The primary namespace for the project
*/

/** \namespace godspeed::outputs
* \brief Contains all classes for output devices
*/

/** \namespace godspeed::inputs
* \brief Contains all classes for input devices
*/

/** \namespace godspeed::framework
* \brief Contains core classes used as building blocks for the rest of the project
*/

#include "vex.h"
#include "inputs/remote-controller.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-collector.h"
#include "outputs/ball-scorer.h"
#include "inputs/path-script.h"

using namespace vex;
using namespace godspeed;
using namespace inputs;
using namespace outputs;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double v = 0.4;
  int t = 2000;
  // Warning! do not attempt to go slower than about 0.4, otherwise drivetrain may not respond as expected!!!
  PathScript::addCommand(0, v, t); //move forward at half speed for 1 second
  PathScript::addCommand(-v, 0, t); //move left at half speed for 1 second
  PathScript::addCommand(0, -v, t); //move backward at half speed for 1 second
  PathScript::addCommand(v, 0, t); //move right at half speed for 1 second
  PathScript::addCommand(0, 0, t); //move right at half speed for 1 second
  OmniDrive3Wheel::xVelocity.connect(PathScript::xDirection);
  OmniDrive3Wheel::yVelocity.connect(PathScript::yDirection);
  OmniDrive3Wheel::angularVelocity.connect(RemoteController::xRightStick);
  PathScript::startTrigger.connect(RemoteController::aButton);
  PathScript::abortTrigger.connect(RemoteController::bButton);
}