/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\anzel                                            */
/*    Created:      Tue Sep 29 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


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
#include "inputs/path-script.h"
#include "inputs/ball-storage-suite.h"
#include "inputs/remote-controller.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-collector.h"
#include "outputs/ball-scorer.h"
#include "inputs/path-script.h"
#include "framework/binder.h"

using namespace vex;
using namespace godspeed;
using namespace inputs;
using namespace outputs;

int main() {
  // Initializations
  vexcodeInit();        //Vex initialization
  Binder::Init();       //Binder initialization
  BallStorage::Init();  //Ball storage suite initialization

  // Bindings
  Binder::Bind(RemoteController::LeftStickX, OmniDrive3Wheel::XSpeed); //Bind the left sticks X position to the drivetrains x-speed
  Binder::Bind(RemoteController::LeftStickY, OmniDrive3Wheel::YSpeed); //Bind the left sticks Y position to the drivetrains y-speed
  Binder::Bind(RemoteController::RightStickX, OmniDrive3Wheel::AngleSpeed); //Bind the right sticks X position to the drivetrains angular speed
  Binder::Bind(RemoteController::LeftTrigger, BallScorer::TreadSpeed); //Bind the left trigger to the center tread
  Binder::Bind(RemoteController::RightTrigger, BallCollector::TreadSpeed); //Bind the right trigger to collector treads
  //BallScorer::ExpanderPosition(360);
  this_thread::yield();
}