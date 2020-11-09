#pragma once
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    namespace outputUtilities
    {
        /// Sets the speed of a motor
        void setMotorSpeed(double motorSpeed, motor &m);
    }

  }// end namespace outputs
}// end namespace godspeed
