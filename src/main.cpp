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
* The primary namespace for the project
*/

#include "vex.h"
#include "inputs/remote-controller.h"
#include "driver-modules/omni-drive-3-wheel.h"

using namespace vex;
using namespace godspeed;

void yay()
{
  Brain.Screen.print("yay!");
  task::sleep(100);
  Brain.Screen.clearScreen();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.setCursor(1, 1);
  OmniDrive3Wheel::xDirection.connect(RemoteController::xLeftStick);
  OmniDrive3Wheel::yDirection.connect(RemoteController::yLeftStick);
}