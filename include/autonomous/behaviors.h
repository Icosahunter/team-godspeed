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
    double AlignAgression = 1;

    /// \brief A pipe function used in the aligning behaviors
    // Determine if the robot is aligned with an object
    double AlignPipe(double d) { return -AlignAgression*d; }

    /// \brief A source function used in some behaviors
    // Stop a function on the robot
    double Stop()            { return 0; }

    /// \brief A source function used in locate object behavior
    // Define the percentage of the drivetrain speed with which
    // the robot should locate an object
    double LocateSpeed()     { return 0.6; }

    /// \brief A source function used in turn left behavior
    // Define the percentage of the drivetrain speed with which 
    // the robot should turn left
    double TurnLeftSpeed()   { return -0.8; }

    /// \brief A source function used in turn right behavior
    // Define the percentage of the drivetrain speed with which
    // the robot should turn right
    double TurnRightSpeed()  { return 0.8; }

    /// \brief A source function used in the score ball behavior
    // Define the percentage of the ball scorer speed for the robot 
    double BallScorerSpeed() { return 1.0; }

    /// \brief A source function used in the ball pickup behavior
    // Define the percentage of the ball pickup speed for the robot 
    double BallPickupSpeed() { return 1.0; }

    /// \brief A source function used in the move forward behavior
    // Define the percentage of the drivetrain speed with which
    // the robot should move forward
    double ForwardSpeed()    { return 1.0; }

    /// \brief A source function used in the move backward behavior
    // Define the percentage of the drivetrain speed with which
    // the robot should move backward
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

    /// \brief A behavior to stop the robot from moving in the x-direction
    Binding StopX(Stop, outputs::OmniDrive3Wheel::XSpeed);

    /// \brief A behavior to stop the robot from moving in the y-direction
    Binding StopY(Stop, outputs::OmniDrive3Wheel::YSpeed);

    /// \brief A behavior to stop the robot from turning
    Binding StopAngle(Stop, outputs::OmniDrive3Wheel::AngleSpeed);

    /// \brief A behavior to stop the robot from moving the ball collectors
    Binding StopCollectors(Stop, outputs::BallCollector::TreadSpeed);

    /// \brief A behavior to stop the robot from moving the ball scorer
    Binding StopScorer(Stop, outputs::BallScorer::TreadSpeed);
  }
}