#pragma once
#include "vex.h"
#include "inputs/ball-storage.h"
#include "inputs/vision-sensor.h"
#include "inputs/range-finders.h"

namespace godspeed
{
  namespace conditions
  {
    /// \brief XOffset threshold at which the robot is considered aligned with an object
    double alignmentThreshold = 0; 
    /// \brief Distance threshold in inches at which a ball is considered near the robot
    double nearBallThreshold = 28; 
    /// \brief Distance threshold in inches at which a goal is considered near the robot
    double nearGoalThreshold = 28; 

    // For ultrasonic rangefinders (not yet implemented)
    double nearObstacleThreshold = 500;

    /// \brief A simple condition which is always True
    bool True() { return true; } 
    /// \brief A simple condition which is always False
    bool False() { return false; } 

    /// \brief Returns true if the number of balls stored in the robot is greater than zero
    bool BallLoaded()
    {
      return inputs::BallStorage::BallCount() > 0;
    }

    /// \brief Returns true if the number of balls stored in the robot is less than zero
    bool BallNotLoaded()
    {
      return inputs::BallStorage::BallCount() == 0;
    }

    /// \brief Returns true if there is a goal in view
    bool GoalTargeted()
    {
      return inputs::VisionSensor::GoalCount() >= 1;
    }

    /// \brief Returns true if there is a ball in view
    bool BallTargeted()
    {
      double b = inputs::VisionSensor::BallCount();
      return b >= 1;
    }

    /// \brief Returns true if the X-offset of the largest goal backboard icon is less than the threshold
    bool AlignedWithGoal()
    {
      double o = inputs::VisionSensor::GoalXOffset();
      return -alignmentThreshold < o && o < alignmentThreshold;
    }

    /// \brief Returns true if the magnitude of the X-offset of the largest ball is less than the threshold
    bool AlignedWithBall()
    {
      double o = inputs::VisionSensor::BallXOffset();
      return -alignmentThreshold < o && o < alignmentThreshold;
    }

    /// \brief Returns true if the Y-offset of the largest ball is greater than the threshold, and remains true for a time after that [EXPERIMENTAL]
    bool NearBall()
    {
      return inputs::VisionSensor::BallDistance() <= nearBallThreshold;
    }

    /// \brief 
    bool NearGoal()
    {
      return inputs::VisionSensor::GoalDistance() <= nearGoalThreshold;
    }

    /// \brief Returns true if the robot is near an obstacle
    bool NearObstacle()
    {
      if (inputs::RangeFinders::LeftDistance() < nearObstacleThreshold || inputs::RangeFinders::RightDistance() < nearObstacleThreshold)
      {
        return true;
      }
      else
      {
        Controller1.Screen.clearScreen();
        return false;
      }
    }
  }
}