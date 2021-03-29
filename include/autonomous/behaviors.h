#pragma once
#include "vex.h"
#include "inputs/vision-sensor.h"
#include "inputs/range-finders.h"
#include "framework/binder.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-scorer.h"
#include "outputs/ball-collector.h"

namespace godspeed
{
  /** 
  * \brief A namespace containing functions for creating autonomous mode behavior bindings
  *
  * When called, behavior functions create a binding with the Binder and then return the ID of the binding created.
  */
  namespace behaviors
  {
    /// \brief A pipe function used in the aligning behaviors
    double AlignPipe(double d)
    {
      return -d;
    }

    /// \brief A source function used in some behaviors
    double Stop()            { return 0; }

    /// \brief A source function used in locate object behaviors
    double LocateSpeed()     { return 0.6; }

    /// \brief A source function used in the score ball behavior
    double BallScorerSpeed() { return 1.0; }

    /// \brief A source function used in the ball pickup behavior
    double BallPickupSpeed() { return 1.0; }

    /// \brief A source function used in the move forward behavior
    double ForwardSpeed()    { return 1.0; }

    /// \brief A behavior that turns the robot to face the largest ball found
    int AlignWithBall()
    {
      return Binder::Bind(inputs::VisionSensor::BallXOffset, AlignPipe,outputs::OmniDrive3Wheel::AngleSpeed);
    }

    /// \brief A behavior that turns the robot to face the largest goal backboard icon found
    int AlignWithGoal()
    {
      return Binder::Bind(inputs::VisionSensor::GoalXOffset, AlignPipe, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    /// \brief A behavior that moves the robot forward
    int MoveForward()
    {
      return Binder::Bind(ForwardSpeed, outputs::OmniDrive3Wheel::YSpeed);
    }

    /// \brief A behavior that turns the robot in place in order to locate an object
    int LocateObject()
    {
      return Binder::Bind(LocateSpeed, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    /// \brief A behavior that turns the center tread to move a ball into the goal
    int ScoreBall()
    {
      return Binder::Bind(BallScorerSpeed, outputs::BallScorer::TreadSpeed);
    }

    /// \brief A behavior that turns the ball collector treads in order to pickup a ball
    int PickUpBall()
    {
      return Binder::Bind(BallPickupSpeed, outputs::BallCollector::TreadSpeed);
    }

    /// \brief A behavior to move the robot away from a detected obstacle [NOT IMPLEMENTED]
    int AvoidObstacle()
    {
      return Binder::Bind(inputs::RangeFinders::Nearness, outputs::OmniDrive3Wheel::XSpeed);
    }

    /// \brief A behavior to move the robot around in a random path [NOT IMPLEMENTED]
    int Wander() //stub
    {
      return 0;
    }

    /// \brief A behavior that sets the robots X-speed to zero
    int StopX()
    {
      return Binder::Bind(Stop, outputs::OmniDrive3Wheel::XSpeed);
    }

    /// \brief A behavior that sets the robots Y-speed to zero
    int StopY()
    {
      return Binder::Bind(Stop, outputs::OmniDrive3Wheel::YSpeed);
    }

    /// \brief A behavior that sets the robots angular speed to zero
    int StopTurn()
    {
      return Binder::Bind(Stop, outputs::OmniDrive3Wheel::AngleSpeed);
    }

    /// \brief A behavior that sets the ball collector treads speeds to zero
    int StopCollectors()
    {
      return Binder::Bind(Stop, outputs::BallCollector::TreadSpeed);
    }

    /// \brief A behavior that sets the center tread speed to zero
    int StopScorer()
    {
      return Binder::Bind(Stop, outputs::BallScorer::TreadSpeed);
    }
  }
}