#pragma once
#include "vex.h"
#include "framework/timed-toggle.h"
#include "framework/lag-value.h"
#include "inputs/ball-storage.h"
#include "inputs/vision-sensor.h"
#include "inputs/range-finders.h"

namespace godspeed
{
  namespace conditions
  {
    double alignmentThreshold = 0; /// \brief XOffset threshold at which the robot is considered aligned with an object
    double nearBallThreshold = 28; /// \brief Distance threshold in inches at which a ball is considered near the robot
    double nearGoalThreshold = 24; /// \brief Distance threshold in inches at which a goal is considered near the robot

    TimedToggle BallCaughtVar(3000);
    TimedToggle GoalCaughtVar(3000);
    void ballcatch() { BallCaughtVar.SetValue(true); }
    void goalcatch() { GoalCaughtVar.SetValue(true); }

    TimedToggle NearBallVar(1500, false, ballcatch);
    TimedToggle NearGoalVar(1500, false, goalcatch);

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

    /// \brief Returns true if the Y-offset of the largest ball is greater than the threshold, and remains true for a time after that [EXPERIMENTAL]
    bool NearBall()
    {
      if (inputs::VisionSensor::BallDistance() <= nearBallThreshold)
      {
        NearBallVar.SetValue(true);
      }
      return NearBallVar.Value();
    }

    /// \brief 
    bool NearGoal()
    {
      if (inputs::VisionSensor::GoalDistance() <= nearGoalThreshold)
      {
        NearGoalVar.SetValue(true);
      }
      return NearGoalVar.Value();
    }

    bool BallCaught()
    {
      return BallCaughtVar.Value();
    }

    bool GoalCaught()
    {
      return GoalCaughtVar.Value();
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