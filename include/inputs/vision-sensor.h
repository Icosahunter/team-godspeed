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

      double ballSize = 0;
      double goalSize = 0;

      double SizeSmoothing = 0.5;

      double XOffset()
      {
        double d;
        if (Vision20.largestObject.centerX != 0.0)
        { d = 1 - Vision20.largestObject.centerX/(ScreenWidth/2); }
        else
        {  d = 0; }
        return d;
      }

      double YOffset()
      {
        double d;
        if (Vision20.largestObject.centerY != 0.0)
        { d = 1 - Vision20.largestObject.centerY/(ScreenHeight/2); }
        else
        {  d = 0; }
        return d;
      }

      double Size()
      {
        return Vision20.largestObject.width * Vision20.largestObject.height;
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
        return XOffset();
      }

      double BallYOffset()
      {
        Vision20.takeSnapshot(Vision20__RED_BALL);
        return YOffset();
      }

      double BallSize()
      {
        Vision20.takeSnapshot(Vision20__RED_BALL);
        double s = Size();
        ballSize = SizeSmoothing*ballSize + (1-SizeSmoothing)*s;
        return ballSize;
      }

      double GoalSize()
      {
        Vision20.takeSnapshot(Vision20__BACKBOARD);
        double s = Size();
        goalSize = SizeSmoothing*goalSize + (1-SizeSmoothing)*s;
        return goalSize;
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
        return XOffset();
      }

      double GoalYOffset()
      {
        Vision20.takeSnapshot(Vision20__BACKBOARD);
        return YOffset();
      }
    }
  }
}