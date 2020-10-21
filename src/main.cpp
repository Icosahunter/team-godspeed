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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "framework/input-controller.h"
#include "inputs/bumper-switch.h"

using namespace vex;
using namespace godspeed;
using namespace framework;

void handleBumperPress(void* args)
{
  Brain.Screen.print("yay!");
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.setCursor(1, 1);
  inputs::BumperSwitch bA = inputs::BumperSwitch(BumperA);
  bA.variables(inputs::switchState)->valueDeviatedEvent.addHandler(handleBumperPress);
  InputController::addInputDevice(bA);
  InputController::start();
}