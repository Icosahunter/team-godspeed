#pragma once
#include "vex.h"
#include "inputs/ball-storage.h"
#include "inputs/vision-sensor.h"
#include "inputs/range-finders.h"

namespace godspeed
{
  namespace conditions
  {
    double alignmentThreshold = 0; /// \brief XOffset threshold at which the robot is considered aligned with an object
    double nearBallThreshold = -0.8; /// \brief YOffset threshold at which a ball is considered near the robot
    double nearGoalThreshold = 0.8; /// \brief YOffset threshold at which a goal is considered near the robot
    double nearBallTimeout = 500; /// \brief time in milliseconds for which a ball is considered near the robot after the threshold was reached
    double nearGoalTimeout = 500; /// \brief time in milliseconds for which a goal is considered near the robot after the threshold was reached

    double nearBall = false;
    double nearGoal = false;

    double nearObstacleThreshold = 500;

    bool True() { return true; } /// \brief A simple condition which is always True
    bool False() { return false; } /// \brief A simple condition which is always False

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

    /// \brief A function used to set the nearBall variable to false after the near ball timeout occurs
    void nearBallFalse() { nearBall = false; }

    /// \brief Returns true if the Y-offset of the largest ball is greater than the threshold, and remains true for a time after that [EXPERIMENTAL]
    bool NearBall()
    {
      if (inputs::VisionSensor::BallYOffset() > nearBallThreshold)
      {
        nearBall = true;
        timer::event(nearBallFalse, nearBallTimeout);
      }
      return nearBall;
    }

    /// \brief A function used to set the nearGoal variable to false after the near goal timeout occurs
    void nearGoalFalse() { nearGoal = false; }

    /// \brief Returns true if the Y-offset of the largest goal backboard icon is greater than the threshold, and remains true for a time after that [EXPERIMENTAL]
    bool NearGoal()
    {
      if (inputs::VisionSensor::GoalYOffset() < nearGoalThreshold)
      {
        nearGoal = true;
        timer::event(nearGoalFalse, nearGoalTimeout);
      }
      return nearGoal;
    }

    /// \brief Returns true if the robot is near an obstacle
    bool NearObstacle()
    {
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("Left: %4.0f", inputs::RangeFinders::leftDistVar);
      Controller1.Screen.newLine();
      Controller1.Screen.print("Right: %4.0f", inputs::RangeFinders::rightDistVar);
      Controller1.Screen.newLine();
      Controller1.Screen.print("Nearness: %4.0f", inputs::RangeFinders::Nearness());

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