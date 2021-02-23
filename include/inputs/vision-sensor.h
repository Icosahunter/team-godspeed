#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    namespace VisionSensor
    {
      signature BallSig = Vision20__RED_BALL;
      signature GoalSig = Vision20__BACKBOARD;
      int ScreenWidth = 600;
      int ScreenHeight = 400;

      double Offset()
      {
        return (ScreenWidth/2) - Vision20.largestObject.centerX;
      }

      double Distance()
      {
        return 0;
      }

      double BallDistance()
      {
        Vision20.takeSnapshot(BallSig);
        return Distance();
      }

      double BallXOffset()
      {
        Vision20.takeSnapshot(BallSig);
        return Offset();
      }

      double BallCount()
      {
        return Vision20.takeSnapshot(BallSig);
      }

      double GoalCount()
      {
        return Vision20.takeSnapshot(GoalSig);
      }

      double GoalDistance()
      {
        Vision20.takeSnapshot(GoalSig);
        return Distance();
      }

      double GoalXOffset()
      {
        Vision20.takeSnapshot(GoalSig);
        return Offset();
      }
    }
  }
}