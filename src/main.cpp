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
}