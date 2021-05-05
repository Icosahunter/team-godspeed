// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision20             vision        19              
// BumperA              bumper        A               
// BumperB              bumper        B               
// Controller1          controller                    
// FrontRightMotor      motor         1               
// FrontLeftMotor       motor         2               
// BackMotor            motor         3               
// LeftCollectorMotor   motor         4               
// RightCollectorMotor  motor         5               
// ScorerMotor          motor         17              
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
#include "mode-control.h"

using namespace vex;
using namespace godspeed;
using namespace ModeControl;

int main()
{
  // Vex initialization
  vexcodeInit();

  //=========== Settings ============
  
  Team  = Team_Blue;
  Robot = Robot_Tchotchke;
  Mode  = Competition_Mode;
  
  //=================================

  // Mode control initialization
  Init();
  
  // Allow other threads to run
  this_thread::yield();
}
