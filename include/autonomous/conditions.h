#pragma once
#include "vex.h"
#include "inputs/ball-storage-suite.h"
#include "inputs/vision-sensor.h"

namespace godspeed
{
  namespace conditions
  {
    double alignmentThreshold = 0;
    double nearBallThreshold = 0.5;
    double nearGoalThreshold = -0.5;
    double nearBallTimeout = 500;
    double nearGoalTimeout = 500;

    double nearBall = false;
    double nearGoal = false;

    bool True() { return true; }
    bool False() { return false; }

    bool BallLoaded()
    {
      return inputs::BallStorage::BallCount() > 0;
    }

    bool BallNotLoaded()
    {
      return inputs::BallStorage::BallCount() == 0;
    }

    bool GoalTargeted()
    {
      return inputs::VisionSensor::GoalCount() >= 1;
    }

    bool BallTargeted()
    {
      double b = inputs::VisionSensor::BallCount();
      return b >= 1;
    }

    bool AlignedWithGoal()
    {
      double o = inputs::VisionSensor::GoalXOffset();
      return -alignmentThreshold < o && o < alignmentThreshold;
    }

    bool AlignedWithBall()
    {
      double o = inputs::VisionSensor::BallXOffset();
      return -alignmentThreshold < o && o < alignmentThreshold;
    }

    void nearBallFalse() { nearBall = false; }

    bool NearBall()
    {
      if (inputs::VisionSensor::BallYOffset() > nearBallThreshold)
      {
        nearBall = true;
        timer::event(nearBallFalse, nearBallTimeout);
      }
      return nearBall;
    }

    void nearGoalFalse() { nearGoal = false; }

    bool NearGoal()
    {
      if (inputs::VisionSensor::GoalYOffset() < nearGoalThreshold)
      {
        nearGoal = true;
        timer::event(nearGoalFalse, nearGoalTimeout);
      }
      return nearGoal;
    }

    bool NearObstacle() //stub
    {
      return false;
    }
  }
}