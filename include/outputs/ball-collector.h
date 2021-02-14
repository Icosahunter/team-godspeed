#pragma once
#include "outputs/output-utilities.h"
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    using namespace OutputUtilities;
    /**
    * \brief A namespace containing functions for controlling the ball collector
    *
    * This namespace contains a single function that corresponds to
    * both collector arm treads.
    */
    namespace BallCollector
    {
      /// \brief Sets the speed of the two collector treads
      void TreadSpeed(double speed)
      {
        setMotorSpeed(speed, LeftCollectorMotor);
        setMotorSpeed(speed, RightCollectorMotor);
      }
    }
  }
}