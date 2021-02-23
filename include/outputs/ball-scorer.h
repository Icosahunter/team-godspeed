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
      double expanderVar;

      /// \brief Sets the speed of the center tread
      void TreadSpeed(double speed)
      {
        setMotorSpeed(speed, ScorerMotor);
      }

      void SpinLeftExpander()
      {
        LeftBallGuideMotor.resetPosition();
        LeftBallGuideMotor.spinToPosition(expanderVar, degrees, false);
      }

      void SpinRightExpander()
      {
        RightBallGuideMotor.resetPosition();
        RightBallGuideMotor.spinToPosition(expanderVar, degrees);
      }

      /// \brief Sets the angular position of the motor that extends the ball guide
      void ExpanderPosition(double angleDeg)
      {
        expanderVar = angleDeg;
        thread t1(SpinLeftExpander);
        thread t2(SpinRightExpander);
        this_thread::yield();
      }
    }
  }
}