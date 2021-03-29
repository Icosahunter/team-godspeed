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
#include "autonomous/behavior-manager.h"
#include "autonomous/behavior-stack.h"
#include "autonomous/state-machine.h"
#include "autonomous/states.h"

using namespace vex;
using namespace godspeed;
using namespace inputs;
using namespace outputs;

void BindDriverControl();
void BindPathScript();

double ExpanderPosition;

double expander_pos() { return ExpanderPosition; }

void SetupTchotchke()
{
  ExpanderPosition = 365;
  conditions::nearGoalThreshold = 30;
  conditions::nearBallThreshold = 28;
  conditions::NearBallVar.Timeout = 1500;
  conditions::NearGoalVar.Timeout = 250;
  conditions::BallCaughtVar = 4000;
  conditions::GoalCaughtVar.Timeout = 10000;
  inputs::VisionSensor::XOffsetFudge = 0.2;
}

void SetupBauble()
{
  ExpanderPosition = 355;
  conditions::nearGoalThreshold = 26;
  conditions::nearBallThreshold = 26;
  conditions::NearBallVar.Timeout = 1500;
  conditions::NearGoalVar.Timeout = 350;
  conditions::BallCaughtVar = 4000;
  conditions::GoalCaughtVar.Timeout = 10000;
  inputs::VisionSensor::XOffsetFudge = 0;
}

int main() {
  // Initializations
  vexcodeInit();           //Vex initialization
  Binder::Init();          //Binder initialization
  BallStorage::Init();     //Ball storage suite initialization
  VisionSensor::Init();    //Vision sensor initialization
  Brain.resetTimer();

  Binder::Bind(expander_pos, BallScorer::ExpanderPosition);   //Bind a constant value (335) to the expander position

  SetupBauble();

  LoadStatesTest();
  StateMachine::Init();

  //LoadBehaviorTest();      //Loads behavior stack
  //BehaviorManager::Init(); //Behavior manager initialization

  //BindDriverControl();

  this_thread::yield();
}

/// \brief Starts a simple path script in which the robot moves in a small square and then stops [FOR TESTING AND DEBUGGING]
void StartPath()
{
  PathScript script = PathScript();
  script.AddCommand( 0.5,  0.0, 0, 2000);
  script.AddCommand( 0.0,  0.5, 0, 2000);
  script.AddCommand(-0.5,  0.0, 0, 2000);
  script.AddCommand( 0.0, -0.5, 0, 2000);
  script.AddCommand( 0.0,  0.0, 0, 2000);
  PathScript::ExecutePath(script);
}

/// \brief Sets up bindings to run a path script
void BindPathScript()
{
  Binder::Bind(PathScript::X, OmniDrive3Wheel::XSpeed);         //Bind the path script x-speed to drivetrains x-speed
  Binder::Bind(PathScript::Y, OmniDrive3Wheel::YSpeed);         //Bind the path script y-speed to drivetrains y-speed
  Binder::Bind(PathScript::Angle, OmniDrive3Wheel::AngleSpeed); //Bind the path script angle speed to drivetrains angle speed
  Controller1.ButtonA.pressed(StartPath);                       //Subscribe start path to the controller's A button being pressed
}

/// \brief Sets up bindings for driver control mode
void BindDriverControl()
{
  // Driver Control Bindings
  Binder::Bind(RemoteController::LeftStickX, OmniDrive3Wheel::XSpeed);      //Bind the left sticks X position to the drivetrains x-speed
  Binder::Bind(RemoteController::LeftStickY, OmniDrive3Wheel::YSpeed);      //Bind the left sticks Y position to the drivetrains y-speed
  Binder::Bind(RemoteController::RightStickX, OmniDrive3Wheel::AngleSpeed); //Bind the right sticks X position to the drivetrains angular speed
  Binder::Bind(RemoteController::LeftTrigger, BallScorer::TreadSpeed);      //Bind the left trigger to the center tread
  Binder::Bind(RemoteController::RightTrigger, BallCollector::TreadSpeed);  //Bind the right trigger to collector treads

  Binder::Bind(RemoteController::UpButton, OmniDrive3Wheel::Forward);       //Bind the up button to moving forward
  Binder::Bind(RemoteController::DownButton, OmniDrive3Wheel::Backward);    //Bind the down button to moving backward
  Binder::Bind(RemoteController::RightButton, OmniDrive3Wheel::Right);      //Bind the right button to moving right
  Binder::Bind(RemoteController::LeftButton, OmniDrive3Wheel::Left);        //Bind the left button to moving left
  
  Binder::Bind(expander_pos, BallScorer::ExpanderPosition);                 //Bind a constant value (335) to the expander position
}
