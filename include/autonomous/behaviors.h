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
      return -d;
    }

    double Stop()            { return 0; }

    double LocateSpeed()     { return 0.5; }

    double BallScorerSpeed() { return 0.5; }

    double BallPickupSpeed() { return 0.5; }

    double ForwardSpeed()    { return 0.5; }

    int AlignWithBall()
    {
      return Binder::Bind(inputs::VisionSensor::BallXOffset, AlignPipe,outputs::OmniDrive3Wheel::AngleSpeed);
    }

    int AlignWithGoal()
    {
      return Binder::Bind(inputs::VisionSensor::GoalXOffset, AlignPipe, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    int MoveForward()
    {
      return Binder::Bind(ForwardSpeed, outputs::OmniDrive3Wheel::YSpeed);
    }

    int LocateObject()
    {
      return Binder::Bind(LocateSpeed, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    int ScoreBall()
    {
      return Binder::Bind(BallScorerSpeed, outputs::BallScorer::TreadSpeed);
    }

    int PickUpBall()
    {
      return Binder::Bind(BallPickupSpeed, outputs::BallCollector::TreadSpeed);
    }

    int AvoidObstacle() //stub
    {
      return 0;
    }

    int Wander() //stub
    {
      return 0;
    }

    int StopX()
    {
      return Binder::Bind(Stop, outputs::OmniDrive3Wheel::XSpeed);
    }

    int StopY()
    {
      return Binder::Bind(Stop, outputs::OmniDrive3Wheel::YSpeed);
    }

    int StopTurn()
    {
      return Binder::Bind(Stop, outputs::OmniDrive3Wheel::AngleSpeed);
    }
  }
}