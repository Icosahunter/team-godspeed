#pragma once
#include "vex.h"
#include "inputs/ball-storage-suite.h"
#include "inputs/vision-sensor.h"

namespace godspeed
{
  namespace conditions
  {
    double ballNearbyThreshold;
    double goalNearbyThreshold;
    double alignmentThreshold;

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
      return inputs::VisionSensor::GoalCount() > 0;
    }

    bool BallTargeted()
    {
      return inputs::VisionSensor::BallCount() > 0;
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

    bool NearBall()
    {
      return inputs::VisionSensor::BallDistance() < ballNearbyThreshold;
    }

    bool NearGoal()
    {
      return inputs::VisionSensor::GoalDistance() < goalNearbyThreshold;
    }

    bool NearObstacle()
    {
      return false;
    }
  }
}