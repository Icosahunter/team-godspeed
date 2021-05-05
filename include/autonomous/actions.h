#pragma once
#include "vex.h"
#include "inputs/vision-sensor.h"
#include "inputs/range-finders.h"
#include "framework/binder.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-scorer.h"
#include "outputs/ball-collector.h"
#include "autonomous/behaviors.h"

namespace godspeed
{
  /// \brief A namespace containing actions for use in autonomous mode
  namespace actions
  {
    using namespace inputs;
    using namespace outputs;
    /// \brief Operation modes for output devices
    enum mode { ON, OFF, LEFT, RIGHT, FORWARD, REVERSE, BACKWARD };

    /// \brief Sets ball collector mode
    void BallCollectors(mode m)
    {
      if (m == ON || m == FORWARD)
      {
        BallCollector::TreadSpeed(1);
      }
      else if (m == REVERSE || m == BACKWARD)
      {
        BallCollector::TreadSpeed(-1);
      }
      else if (m == OFF)
      {
        BallCollector::TreadSpeed(0);
      }
    }

    /// \brief Sets ball scorer mode
    void BallScorer(mode m)
    {
      if (m == ON || m == FORWARD)
      { 
        BallScorer::TreadSpeed(1);
      }
      else if (m == REVERSE || m == BACKWARD)
      {
        BallScorer::TreadSpeed(-1);
      }
      else if (m == OFF)
      { 
        BallScorer::TreadSpeed(0);
      }
    }

    /// \brief Sets drivetrain movement mode
    void Drive(mode m)
    {
      if (m == ON || m == FORWARD)
      { 
        Binder::AddBinding(behaviors::MoveForward);
        Binder::RemoveBinding(behaviors::MoveBackward);
        Binder::RemoveBinding(behaviors::StopY);
      }
      else if (m == REVERSE || m == BACKWARD)
      { 
        Binder::AddBinding(behaviors::MoveBackward);
        Binder::RemoveBinding(behaviors::MoveForward);
        Binder::RemoveBinding(behaviors::StopY);
      }
      else if (m == OFF)
      {
        Binder::AddBinding(behaviors::StopY);
        Binder::RemoveBinding(behaviors::MoveBackward);
        Binder::RemoveBinding(behaviors::MoveForward);
      }
    }

    /// \brief Sets drivetrain movement mode for a time interval
    void Drive(mode m, int dur)
    {
      Drive(m);
      task::sleep(dur);
      Drive(OFF);
    }

    /// \brief Sets drivetrain turning mode
    void Turn(mode m)
    {
      if (m == RIGHT)
      { 
        OmniDrive3Wheel::AngleSpeed(0.8);
      }
      else if (m == LEFT)
      { 
        OmniDrive3Wheel::AngleSpeed(-0.8);
      }
      else if (m == OFF)
      {
        OmniDrive3Wheel::AngleSpeed(0);
      }
    }

    /// \brief Sets drivetrain turning mode for a time interval
    void Turn(mode m, int dur)
    {
      Turn(m);
      task::sleep(dur);
      Turn(OFF);
    }
  }
}