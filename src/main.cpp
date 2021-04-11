// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision20             vision        20              
// BumperA              bumper        A               
// BumperB              bumper        B               
// Controller1          controller                    
// FrontRightMotor      motor         1               
// FrontLeftMotor       motor         2               
// BackMotor            motor         3               
// LeftCollectorMotor   motor         4               
// RightCollectorMotor  motor         5               
// ScorerMotor          motor         7               
// LeftBallGuideMotor   motor         8               
// RightBallGuideMotor  motor         9               
// LeftRangeFinder      sonar         E, F            
// RightRangeFinder     sonar         C, D            
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision20             vision        20              
// BumperA              bumper        A               
// BumperB              bumper        B               
// Controller1          controller                    
// FrontRightMotor      motor         1               
// FrontLeftMotor       motor         2               
// BackMotor            motor         3               
// LeftCollectorMotor   motor         4               
// RightCollectorMotor  motor         5               
// ScorerMotor          motor         7               
// LeftBallGuideMotor   motor         8               
// RightBallGuideMotor  motor         9               
// LeftRangeFinder      sonar         E, F            
// RightRangeFinder     sonar         C, D            
// ---- END VEXCODE CONFIGURED DEVICES ----
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
* \brief Contains all classes and namespaces for output devices
*/

/** \namespace godspeed::inputs
* \brief Contains all classes and namespaces for input devices
*/

/** \namespace godspeed::framework
* \brief Contains core classes and functions used as building blocks for the rest of the project
*/

#include "vex.h"
#include "inputs/path-script.h"
#include "inputs/ball-storage.h"
#include "inputs/range-finders.h"
#include "inputs/remote-controller.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-collector.h"
#include "outputs/ball-scorer.h"
#include "inputs/path-script.h"
#include "framework/binder.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"
#include "autonomous/state-machine.h"
#include "autonomous/bauble-states.h"
#include "autonomous/tchotchke-states.h"
#include "driver-control.h"

using namespace vex;
using namespace godspeed;
using namespace inputs;
using namespace outputs;

int main() {

  // Initializations
  vexcodeInit();           //Vex initialization
  Binder::Init();          //Binder initialization
  BallStorage::Init();     //Ball storage suite initialization
  VisionSensor::Init();    //Vision sensor initialization
  Brain.resetTimer();

  Tchotchke::StartAutonomous();
  StateMachine::Init();

  //DriverControl::BindDriverControl();

  this_thread::yield();
}
