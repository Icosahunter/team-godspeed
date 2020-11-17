#pragma once
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    /// \brief A namespace for utility functions used by output classes
    namespace outputUtilities
    {
        /** 
        * \brief Sets the speed of a motor
        *
        * Takes a value -1 to 1 and sets the velocity
        * appropriately. Has a "dead zone" of -0.1 to 0.1
        * which it treats as equal to zero (no movement)
        */
        void setMotorSpeed(double motorSpeed, motor &m);
    }

  }// end namespace outputs
}// end namespace godspeed
