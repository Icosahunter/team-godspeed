#include "outputs/omni-drive-3-wheel.h"

namespace godspeed 
{
  namespace outputs
  {
    DataSinkD OmniDrive3Wheel::xDirection = DataSinkD(-1, 1, update);
    DataSinkD OmniDrive3Wheel::yDirection = DataSinkD(-1, 1, update);

    void OmniDrive3Wheel::update()
    {
      double x = xDirection.value();
      double y = yDirection.value();
      double ang = atan2(y, x);
      double mag = sqrt(pow(y, 2) + pow(x, 2));
      double m1spd = mag*(2.0/3)*cos(ang + M_PI/3);
      double m2spd = mag*(2.0/3)*cos(ang + 5*M_PI/3);
      double m3spd = mag*(2.0/3)*cos(ang + M_PI);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(x);
      Brain.Screen.newLine();
      Brain.Screen.print(y);
      Brain.Screen.newLine();
      task::sleep(100);
      Brain.Screen.clearScreen();
      setMotorSpeed(m1spd, Motor1);
      setMotorSpeed(m2spd, Motor2);
      setMotorSpeed(m3spd, Motor3);
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
  }
}