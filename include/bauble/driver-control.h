#pragma once
#include "bauble.h"
#include "inputs/remote-controller.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-collector.h"
#include "outputs/ball-scorer.h"
#include "/framework/binder.h"
#include "framework/smoothing.h"
#include "vex.h"

namespace godspeed
{
  namespace Bauble
  {
    using namespace inputs;
    using namespace outputs;
    Binding DCtrl_XSpeed(RemoteController::LeftStickX, OmniDrive3Wheel::XSpeed);               //Bind the left sticks X position to the drivetrains x-speed
    Binding DCtrl_YSpeed(RemoteController::LeftStickY, OmniDrive3Wheel::YSpeed);               //Bind the left sticks Y position to the drivetrains y-speed
    Binding DCtrl_AngleSpeed(RemoteController::RightStickX, OmniDrive3Wheel::AngleSpeed);      //Bind the right sticks X position to the drivetrains angular speed
    Binding DCtrl_CenterTread(RemoteController::LeftTrigger, BallScorer::TreadSpeed);          //Bind the left trigger to the center tread
    Binding DCtrl_CollectorTreads(RemoteController::RightTrigger, BallCollector::TreadSpeed);  //Bind the right trigger to collector treads
    Binding DCtrl_EnableSaturation(RemoteController::AButton, OmniDrive3Wheel::EnableSaturation);

    /// \brief Bind Bauble driver control
    void BindDriverControl()
    {
      Binder::AddBinding(ExpanderBinding);
      Binder::AddBinding(DCtrl_XSpeed);
      Binder::AddBinding(DCtrl_YSpeed);
      Binder::AddBinding(DCtrl_AngleSpeed);
      Binder::AddBinding(DCtrl_CenterTread);
      Binder::AddBinding(DCtrl_CollectorTreads);
      Binder::AddBinding(DCtrl_EnableSaturation);
    }

    /// \brief Un-bind Bauble driver control
    void UnBindDriverControl()
    {
      Binder::RemoveBinding(DCtrl_XSpeed);
      Binder::RemoveBinding(DCtrl_YSpeed);
      Binder::RemoveBinding(DCtrl_AngleSpeed);
      Binder::RemoveBinding(DCtrl_CenterTread);
      Binder::RemoveBinding(DCtrl_CollectorTreads);
      Binder::RemoveBinding(DCtrl_EnableSaturation);
    }
  }
}