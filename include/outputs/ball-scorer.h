#pragma once
#include "outputs/output-utilities.h"
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    using namespace OutputUtilities;
    /**
    * \brief A namespace containing functions for controlling the ball scorer
    *
    * This class contains two functions, one for the center tread and one
    * for the ball guide expander.
    */
    namespace BallScorer
    {
      void TreadSpeed(double speed)
      {
        setMotorSpeed(speed, ScorerMotor);
      }

      void ExpanderPosition(double angleDeg)
      {
        ballGuideMotor.resetPosition();
        ballGuideMotor.spinToPosition(angleDeg, degrees);
      }
    }
  }
}