#pragma once
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    /// \brief A namespace for utility functions used by output classes
    namespace OutputUtilities
    {
        /** 
        * \brief Sets the speed of a motor
        *
        * Takes a value -1 to 1 and sets the velocity
        * appropriately. Has a "dead zone" of -0.1 to 0.1
        * which it treats as equal to zero (no movement)
        */
      void setMotorSpeed(double motorSpeed, motor &m)
      {
        // if motor speed is out of bounds, set to nearest boundary value
        if (std::abs(motorSpeed) > 1)
        {
          m.setVelocity(100, percentUnits::pct);
          m.spin(forward);
        }

        // if motor speed is out of bounds, set to nearest boundary value
        else if (std::abs(motorSpeed) > 0.1)
        {
          m.setVelocity(100*motorSpeed, percentUnits::pct);
          m.spin(forward);
        }

        // otherwise, stop the motor
        else
        {
          m.stop();
        }
      }
    }
  }
}
