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
  /// \brief A namespace containing autonomous mode behavior bindings
  namespace behaviors
  {
    /// \brief A pipe function used in the aligning behaviors
    double AlignPipe(double d) { return -d; }

    /// \brief A source function used in some behaviors
    double Stop()            { return 0; }

    /// \brief A source function used in locate object behavior
    double LocateSpeed()     { return 0.6; }

    /// \brief A source function used in turn left behavior
    double TurnLeftSpeed()   { return -0.8; }

    /// \brief A source function used in turn right behavior
    double TurnRightSpeed()  { return 0.8; }

    /// \brief A source function used in the score ball behavior
    double BallScorerSpeed() { return 1.0; }

    /// \brief A source function used in the ball pickup behavior
    double BallPickupSpeed() { return 1.0; }

    /// \brief A source function used in the move forward behavior
    double ForwardSpeed()    { return 1.0; }

    /// \brief A source function used in the move backward behavior
    double BackwardSpeed()   { return -1.0; }

    /// \brief A behavior that turns the robot to face the largest ball found
    Binding AlignWithBall(inputs::VisionSensor::BallXOffset, AlignPipe, outputs::OmniDrive3Wheel::AngleSpeed);

    /// \brief A behavior that turns the robot to face the largest goal backboard icon found
    Binding AlignWithGoal(inputs::VisionSensor::GoalXOffset, AlignPipe, outputs::OmniDrive3Wheel::AngleSpeed);

    /// \brief A behavior that moves the robot forward
    Binding MoveForward(ForwardSpeed, outputs::OmniDrive3Wheel::YSpeed);

    /// \brief A behavior that moves the robot forward
    Binding MoveBackward(BackwardSpeed, outputs::OmniDrive3Wheel::YSpeed);

    /// \brief A behavior that turns the robot left
    Binding TurnLeft(TurnLeftSpeed, outputs::OmniDrive3Wheel::AngleSpeed);

    /// \brief A behavior that turns the robot right
    Binding TurnRight(TurnRightSpeed, outputs::OmniDrive3Wheel::AngleSpeed);

    /// \brief A behavior that turns the robot in place in order to locate an object
    Binding LocateObject(LocateSpeed, outputs::OmniDrive3Wheel::AngleSpeed);

    /// \brief A behavior that turns the center tread to move a ball into the goal
    Binding ScoreBall(BallScorerSpeed, outputs::BallScorer::TreadSpeed);

    /// \brief A behavior that turns the ball collector treads in order to pickup a ball
    Binding PickUpBall(BallPickupSpeed, outputs::BallCollector::TreadSpeed);

    /// \brief A behavior to move the robot away from a detected obstacle
    Binding AvoidObstacle(inputs::RangeFinders::Nearness, outputs::OmniDrive3Wheel::XSpeed);

    Binding StopX(Stop, outputs::OmniDrive3Wheel::XSpeed);

    Binding StopY(Stop, outputs::OmniDrive3Wheel::YSpeed);

    Binding StopAngle(Stop, outputs::OmniDrive3Wheel::AngleSpeed);

    Binding StopCollectors(Stop, outputs::BallCollector::TreadSpeed);

    Binding StopScorer(Stop, outputs::BallScorer::TreadSpeed);
  }
}