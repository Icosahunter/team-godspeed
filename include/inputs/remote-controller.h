#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    /// \brief A namespace containing functions for accessing all remote controller inputs.
    namespace RemoteController
    {
      double UpButton() { return (double)Controller1.ButtonUp.pressing(); }
      double DownButton() { return (double)Controller1.ButtonDown.pressing(); }
      double RightButton() { return (double)Controller1.ButtonRight.pressing(); }
      double LeftButton() { return (double)Controller1.ButtonLeft.pressing(); }
      double XButton() { return (double)Controller1.ButtonX.pressing(); }
      double YButton() { return (double)Controller1.ButtonY.pressing(); }
      double AButton() { return (double)Controller1.ButtonA.pressing(); }
      double BButton() { return (double)Controller1.ButtonB.pressing(); }
      double RightTrigger() { return (double)Controller1.ButtonR2.pressing(); }
      double RightBumper() { return (double)Controller1.ButtonR1.pressing(); }
      double LeftTrigger() { return (double)Controller1.ButtonL2.pressing(); }
      double LeftBumper() { return (double)Controller1.ButtonL1.pressing(); }
      double LeftStickX() { return (double)Controller1.Axis4.position(); }
      double LeftStickY() { return (double)Controller1.Axis3.position(); }
      double RightStickX() { return (double)Controller1.Axis1.position(); }
      double RightStickY() { return (double)Controller1.Axis2.position(); }
    }
  }
}