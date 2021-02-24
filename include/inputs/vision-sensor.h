#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    namespace VisionSensor
    {
      double ScreenWidth = 315;
      double ScreenHeight = 210;

      double ballCount = 0;
      double goalCount = 0;

      double CountSmoothing = 0.125;

      double Offset()
      {
        double d;
        if (Vision20.largestObject.centerX != 0.0)
        {
          d = (ScreenWidth/2) - Vision20.largestObject.centerX;
        }
        else
        {
          d = 0;
        }
        return d;
      }

      double Distance()
      {
        return 0;
      }

      double BallDistance()
      {
        Vision20.takeSnapshot(Vision20__RED_BALL);
        return Distance();
      }

      double BallXOffset()
      {
        Vision20.takeSnapshot(Vision20__RED_BALL);
        return Offset();
      }

      double BallCount()
      {
        int n = Vision20.takeSnapshot(Vision20__RED_BALL);
        ballCount = CountSmoothing*ballCount + (1-CountSmoothing)*n;
        return ballCount;
      }

      double GoalCount()
      {
        int n = Vision20.takeSnapshot(Vision20__BACKBOARD);
        goalCount = CountSmoothing*goalCount + (1-CountSmoothing)*n;
        return goalCount;
      }

      double GoalDistance()
      {
        Vision20.takeSnapshot(Vision20__BACKBOARD);
        return Distance();
      }

      double GoalXOffset()
      {
        Vision20.takeSnapshot(Vision20__BACKBOARD);
        return Offset();
      }
    }
  }
}