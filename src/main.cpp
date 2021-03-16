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

void BindDriverControl();
void BindPathScript();

int main() {
  // Initializations
  vexcodeInit();        //Vex initialization
  Binder::Init();       //Binder initialization
  BallStorage::Init();  //Ball storage suite initialization

  BindPathScript();  //Setup Path Script bindings
//  BindDriverControl(); //Setup Driver Control bindings

  this_thread::yield();
}

double v = 1.0; // motor power (1.0 = 100% power)
double t = 3000; // Time to move in that direction (ms)

void StartPath1()
{
  PathScript script = PathScript();
/*  
  // Drivetrain Experiment Script 1
  script.AddCommand(0, v, 0, t); // move forward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, v, 0, t); // move forward-left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand( v, 0, 0, t); // move right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, -v, 0, t); // move backward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(v, v, 0, t); // move forward-right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, -v, 0, t); // move backward-left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(v, -v, 0, t); // move backward-right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, 0, 0, t); // move left at v% speed for t ms
*/
  script.AddCommand(0, v, 0, t); // move forward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, 0, 0, t); // move left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, -v, 0, t); // move backward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand( v, 0, 0, t); // move right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, 0, 0, t); // stop moving
  PathScript::ExecutePath(script);
}

void StartPath2()
{
  PathScript script = PathScript();
/*
  // Drivetrain Experiment Script 2
  script.AddCommand( v, 0, 0, t); // move right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, v, 0, t); // move forward-left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(v, v, 0, t); // move forward-right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, -v, 0, t); // move backward-left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, v, 0, t); // move forward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(-v, 0, 0, t); // move left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(v, -v, 0, t); // move backward-right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, -v, 0, t); // move backward at v% speed for t ms
*/
  script.AddCommand(-v, 0, 0, t); // move left at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, v, 0, t); // move forward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand( v, 0, 0, t); // move right at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, -v, 0, t); // move backward at v% speed for t ms
  script.AddCommand(0, 0, 0, t/4.0); // stop moving
  script.AddCommand(0, 0, 0, t); // stop moving
  PathScript::ExecutePath(script);
}
void BindPathScript()
{
  Binder::Bind(PathScript::X, OmniDrive3Wheel::XSpeed);         //Bind the path script x-speed to drivetrains x-speed
  Binder::Bind(PathScript::Y, OmniDrive3Wheel::YSpeed);         //Bind the path script y-speed to drivetrains y-speed
  Binder::Bind(PathScript::Angle, OmniDrive3Wheel::AngleSpeed); //Bind the path script angle speed to drivetrains angle speed
  Controller1.ButtonA.pressed(StartPath1);                       //Subscribe start path to the controller's A button being pressed
  Controller1.ButtonB.pressed(StartPath2);                       //Subscribe start path to the controller's A button being pressed
}

void BindDriverControl()
{
  // Driver Control Bindings
  Binder::Bind(RemoteController::LeftStickX, OmniDrive3Wheel::XSpeed);      //Bind the left sticks X position to the drivetrains x-speed
  Binder::Bind(RemoteController::LeftStickY, OmniDrive3Wheel::YSpeed);      //Bind the left sticks Y position to the drivetrains y-speed
  Binder::Bind(RemoteController::RightStickX, OmniDrive3Wheel::AngleSpeed); //Bind the right sticks X position to the drivetrains angular speed
  Binder::Bind(RemoteController::LeftTrigger, BallScorer::TreadSpeed);      //Bind the left trigger to the center tread
  Binder::Bind(RemoteController::RightTrigger, BallCollector::TreadSpeed);  //Bind the right trigger to collector treads


//  Binder::Bind(RemoteController::UpButton, OmniDrive3Wheel::Forward);       //Bind the up button to moving forward
//  Binder::Bind(RemoteController::DownButton, OmniDrive3Wheel::Backward);    //Bind the down button to moving backward
//  Binder::Bind(RemoteController::RightButton, OmniDrive3Wheel::Right);      //Bind the right button to moving right
//  Binder::Bind(RemoteController::LeftButton, OmniDrive3Wheel::Left);        //Bind the left button to moving left
  BallScorer::ExpanderPosition(0);//365);
}