#pragma once
#include "vex.h"
#include "inputs/vision-sensor.h"
#include "framework/binder.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-scorer.h"
#include "outputs/ball-collector.h"

namespace godspeed
{
  namespace behaviors
  {
    double AlignPipe(double d)
    {
      return d/((double)inputs::VisionSensor::ScreenWidth);
    }

    double LocateSpeed()     { return 0.5; }

    double BallScorerSpeed() { return 0.5; }

    double BallPickupSpeed() { return 0.5; }

    double BallTrackSpeed()  { return 0.5; }

    int AlignWithBallBehavior()
    {
      return Binder::Bind(inputs::VisionSensor::BallXOffset,AlignPipe,outputs::OmniDrive3Wheel::AngleSpeed);
    }

    int AlignWithGoalBehavior()
    {
      return Binder::Bind(inputs::VisionSensor::GoalXOffset, AlignPipe, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    int TrackBallBehavior()
    {
      return Binder::Bind(BallTrackSpeed, outputs::OmniDrive3Wheel::YSpeed);
    }

    int LocateObjectBehavior()
    {
      return Binder::Bind(LocateSpeed, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    int ScoreBallBehavior()
    {
      return Binder::Bind(BallScorerSpeed, outputs::BallScorer::TreadSpeed);
    }

    int PickUpBallBehavior()
    {
      return Binder::Bind(BallPickupSpeed, outputs::BallCollector::TreadSpeed);
    }
  }
}