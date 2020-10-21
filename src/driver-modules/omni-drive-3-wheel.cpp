#include "driver-modules/omni-drive-3-wheel.h"
#include "framework/driver-module.h"
#include "vex.h"
#include <cmath>

namespace godspeed 
{
  namespace driverModules
  {
    OmniDrive3Wheel::OmniDrive3Wheel(motor &m1, motor &m2, motor &m3)
    {
      motor1_ = &m1;
      motor2_ = &m2;
      motor3_ = &m3;
    }

    void OmniDrive3Wheel::update()
    {
      double x = framework::InputVariable::rescale(-1, 1, *ySpeed_);
      double y = framework::InputVariable::rescale(-1, 1, *xSpeed_);
      double ang = atan2(y, x);
      double mag = sqrt(pow(y, 2) + pow(x, 2));
      double m1spd = mag*(2.0/3)*cos(ang + M_PI/3);
      double m2spd = mag*(2.0/3)*cos(ang + 5*M_PI/3);
      double m3spd = mag*(2.0/3)*cos(ang + M_PI);
      setMotorSpeed(m1spd, *motor1_);
      setMotorSpeed(m2spd, *motor2_);
      setMotorSpeed(m3spd, *motor3_);
    }

    void OmniDrive3Wheel::setMotorSpeed(double motorSpeed, motor &m)
    {
      if (motorSpeed < 0)
      {
        m.setReversed(false);
        if (motorSpeed < -1)
        {
          m.setVelocity(100*motorSpeed, percentUnits::pct);
        }
        else
        {
          m.setVelocity(100, percentUnits::pct);
        }
      }
      else if (motorSpeed > 0)
      {
        m.setReversed(true);
        if (motorSpeed > 1)
        {
          m.setVelocity(100*motorSpeed, percentUnits::pct);
        }
        else
        {
          m.setVelocity(100, percentUnits::pct);
        }
      }
      else
      {
        m.setVelocity(0, percentUnits::pct);
      }
    }

    void OmniDrive3Wheel::connect(int slot, framework::InputVariable &var, framework::InputVariable::InputVariableEvent evt)
    {
      if (slot == xDirection)
      {
        if (xSpeed_ != nullptr)
        {
          Brain.Screen.print("Error: Slot already filled!");
        }
        else
        {
          addDependency(var, evt);
          xSpeed_ = &var;
        }
      }
      else if (slot == yDirection)
      {
        if (ySpeed_ != nullptr)
        {
          Brain.Screen.print("Error: Slot already filled!");
        }
        {
          addDependency(var, evt);
          ySpeed_ = &var;
        }
      }
    }


  }
}