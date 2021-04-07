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
    
    // Define the bindings between the software and the VEX controller
    Binding DCtrl_XSpeed(RemoteController::LeftStickX, OmniDrive3Wheel::XSpeed);               //Bind the left sticks X position to the drivetrains x-speed
    Binding DCtrl_YSpeed(RemoteController::LeftStickY, OmniDrive3Wheel::YSpeed);               //Bind the left sticks Y position to the drivetrains y-speed
    Binding DCtrl_AngleSpeed(RemoteController::RightStickX, OmniDrive3Wheel::AngleSpeed);      //Bind the right sticks X position to the drivetrains angular speed
    Binding DCtrl_CenterTread(RemoteController::LeftTrigger, BallScorer::TreadSpeed);          //Bind the left trigger to the center tread
    Binding DCtrl_CollectorTreads(RemoteController::RightTrigger, BallCollector::TreadSpeed);  //Bind the right trigger to collector treads

    // Define the ball scorer expander and how many degrees to rotate it
    double expander_pos() { return 355; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);

    // Turn on driver control (Add all driver control bindings to the binder)
    void BindDriverControl()
    {
      Binder::AddBinding(ExpanderBinding);
      Binder::AddBinding(DCtrl_XSpeed);
      Binder::AddBinding(DCtrl_YSpeed);
      Binder::AddBinding(DCtrl_AngleSpeed);
      Binder::AddBinding(DCtrl_CenterTread);
      Binder::AddBinding(DCtrl_CollectorTreads);
    }

    // Turn off driver control (Remove all driver control bindings from the binder)
    void UnBindDriverControl()
    {
      Binder::RemoveBinding(DCtrl_XSpeed);
      Binder::RemoveBinding(DCtrl_YSpeed);
      Binder::RemoveBinding(DCtrl_AngleSpeed);
      Binder::RemoveBinding(DCtrl_CenterTread);
      Binder::RemoveBinding(DCtrl_CollectorTreads);
    }
  }
}