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

      /// \brief Initialization for ball scorer, zeroes out position of left and right ball guide motors
      void Init()
      {
        LeftBallGuideMotor.resetPosition();
        RightBallGuideMotor.resetPosition();
      }

      /// \brief Sets the speed of the center tread
      void TreadSpeed(double speed)
      {
        setMotorSpeed(-speed, ScorerMotor);
      }

      /// \brief Spins the left expander motor to the value stored in expanderVar
      void SpinLeftExpander()
      {
        LeftBallGuideMotor.spinToPosition(expanderVar, degrees, false);
      }

      /// \brief Spins the right expander motor to the value stored in expanderVar
      void SpinRightExpander()
      {
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

      /// \brief Stops ball scorer tread
      void Stop()
      {
        TreadSpeed(0);
      }
    }
  }
}