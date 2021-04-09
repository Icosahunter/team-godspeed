#pragma once
#include "inputs/remote-controller.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-collector.h"
#include "outputs/ball-scorer.h"
#include "framework/binder.h"
#include "vex.h"

namespace godspeed
{
  namespace DriverControl
  {
    using namespace inputs;
    using namespace outputs;
    
    // Function to reverse the direction of a motor
    double reverse(double d){ return -d; }

    // Define the bindings between the software and the VEX controller
    Binding DCtrl_XSpeed(RemoteController::LeftStickX, OmniDrive3Wheel::XSpeed);               //Bind the left sticks X position to the drivetrains x-speed
    Binding DCtrl_YSpeed(RemoteController::LeftStickY, OmniDrive3Wheel::YSpeed);               //Bind the left sticks Y position to the drivetrains y-speed
    Binding DCtrl_AngleSpeed(RemoteController::RightStickX, OmniDrive3Wheel::AngleSpeed);      //Bind the right sticks X position to the drivetrains angular speed
    Binding DCtrl_CenterTread(RemoteController::LeftTrigger, BallScorer::TreadSpeed);          //Bind the left trigger to the center tread
    //Binding DCtrl_CenterTread_Reverse(RemoteController::LeftBumper, reverse, BallScorer::TreadSpeed);   //Bind the left bumper to the center tread
    Binding DCtrl_CollectorTreads(RemoteController::RightTrigger, BallCollector::TreadSpeed);  //Bind the right trigger to collector treads
    //Binding DCtrl_CollectorTreads_Reverse(RemoteController::RightBumper, reverse, BallCollector::TreadSpeed);  //Bind the right bumper to collector treads
    //Binding DCtrl_ExpanderBinding_Up(RemoteController::UpButton, outputs::BallScorer::ExpanderPosition); //Bind the Up button to the Ball Scorer Expander
    //Binding DCtrl_ExpanderBinding_Down(RemoteController::DownButton, reverse, outputs::BallScorer::ExpanderPosition); //Bind the Down button to the Ball Scorer Expander

    // Define the ball scorer expander and how many degrees to rotate it
    double expander_pos() { return 365; }    // For Tchotchke (larger robot)
    //double expander_pos() { return 350; }    // For Bauble (smaller robot)
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);

    // Turn on driver control (Add all driver control bindings to the binder)
    void BindDriverControl()
    {
      Binder::AddBinding(ExpanderBinding); // Remove for Competition
      Binder::AddBinding(DCtrl_XSpeed);
      Binder::AddBinding(DCtrl_YSpeed);
      Binder::AddBinding(DCtrl_AngleSpeed);
      Binder::AddBinding(DCtrl_CenterTread);
      Binder::AddBinding(DCtrl_CollectorTreads);
      //Binder::AddBinding(DCtrl_ExpanderBinding_Up);
      //Binder::AddBinding(DCtrl_ExpanderBinding_Down);
    }

    // Turn off driver control (Remove all driver control bindings from the binder)
    void UnBindDriverControl()
    {
      Binder::RemoveBinding(DCtrl_XSpeed);
      Binder::RemoveBinding(DCtrl_YSpeed);
      Binder::RemoveBinding(DCtrl_AngleSpeed);
      Binder::RemoveBinding(DCtrl_CenterTread);
      Binder::RemoveBinding(DCtrl_CollectorTreads);
      //Binder::RemoveBinding(DCtrl_ExpanderBinding_Up);
      //Binder::RemoveBinding(DCtrl_ExpanderBinding_Down);
    }
  }
}