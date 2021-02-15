#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    namespace VisionSensor
    {
      signature BallSig = Vision20__RED_BALL;

      double BallDistance()
      {
        return 0;
      }

      double BallOffset()
      {
        return 0;
      }

      double BallCount()
      {
        return Vision20.takeSnapshot(BallSig);
      }

      double GoalCount()
      {
        return Vision20.takeSnapshot(Vision20__BACKBOARD);
      }

      double GoalDistance()
      {
        return 0;
      }

      double GoalOffset()
      {
        return 0;
      }
    }
  }
}