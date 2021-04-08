#pragma once
#include "vex.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  namespace Bauble
  {
    // Get into position once the match starts
    void ent1()
    {
      // Move forward far enough to easily identify the backboard and align
      DO_FOR(behaviors::MoveForward, 2700); // move forward (time in ms)
      DO_FOR(behaviors::StopY, 500); // To flush out the averaging array
      
      // Turn right to face the tower in the home row right corner
      DO_FOR(behaviors::TurnRight, 2150); // turn right (time in ms)
      DO_FOR(behaviors::StopAngle, 500); // To flush out the averaging array
    }

    // Approach goal in home row right corner, pickup the ball on the ground,
    // and score the ball that was preloaded
    void ent2()
    {
      // In case of past distance data, initialize new goal distance to infinity
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      
      // Start ball scorer and ball pickup 
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1200);

      // Stop the robot in front of the tower to finish scoring
      DO_FOR(behaviors::StopY, 1000);
      
      // Finish picking up ball and back away from the tower
      Binder::AddBinding(behaviors::PickUpBall);
      DO_FOR(behaviors::MoveBackward, 2900);
      
      // Stop the ball scorer and ball pickup
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);
      
      // Stop backing up, turn to face the autonomous goal on the right edge
      DO_FOR(behaviors::StopY, 450);
      DO_FOR(behaviors::TurnLeft, 2000);
    }

    // Approach and score the ball in the autonomous goal on the right edge,
    // then remove the opponent's ball from the bottom of the tower
    void ent3()
    {
      // Remove past behaviors
      outputs::OmniDrive3Wheel::AngleSpeed(0);

      // In case of past distance data, initialize new goal distance to infinity
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      
      // Approach goal
      WAIT(550);
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::MoveForward);
      Binder::AddBinding(behaviors::TurnLeft);
      WAIT(500);
      
      // Move forward slightly to push the ball out or grab it
      Binder::RemoveBinding(behaviors::MoveForward);
      Binder::AddBinding(behaviors::StopY);
      WAIT(1500);

      // Turn left to remove the ball from the tower
      Binder::RemoveBinding(behaviors::TurnLeft);
      Binder::RemoveBinding(behaviors::StopY);

      // Stop the ball pickup
      Binder::RemoveBinding(behaviors::PickUpBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      DO_FOR(behaviors::MoveBackward, 800);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 1500);
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      DO_FOR(behaviors::MoveBackward, 2000);
    }
    
    void ent4()
    {
      // Finish scoring
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1000);
      DO_FOR(behaviors::StopY, 500);
      WAIT(2000);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
      DO_FOR(behaviors::MoveBackward, 1000);
    }

    // Define the ball scorer expander and how many degrees to rotate it
    double expander_pos() { return 350; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);

    void StartAutonomous()
    {
      // Fine-tuning for Bauble to perform better (fudge numbers for the smaller robot)
      inputs::VisionSensor::XOffsetFudge = 0.1;

      // Initialize the ball storage counter with the preloaded ball
      inputs::BallStorage::BallCounter = 1;

      behaviors::AlignAgression = 1;

      // Add the binding for the ball scorer expander to the list
      Binder::AddBinding(ExpanderBinding);

      // Define state names
      static State s1;
      static State s2;
      static State s3;
      static State s4;
      static State s5;
      static State sStop;

      // Define entry action, activities, exit conditions, and exit actions
      s1.AddEntryAction(ent1);
      s1.AddActivity(behaviors::AlignWithGoal);
      s1.AddActivity(behaviors::MoveForward);
      s1.AddTransition(conditions::NearGoal, s2);

      // Define entry action, activities, exit conditions, and exit actions
      s2.AddEntryAction(ent2);
      s2.AddActivity(behaviors::AlignWithGoal);
      s2.AddActivity(behaviors::MoveForward);
      s2.AddTransition(conditions::NearGoal, s3);

      // Define entry action, activities, exit conditions, and exit actions
      s3.AddEntryAction(ent3);
      s3.AddActivity(behaviors::AlignWithGoal);
      s3.AddActivity(behaviors::MoveForward);
      s3.AddTransition(conditions::NearGoal, s4);

      s4.AddEntryAction(ent4);
      s4.AddTransition(conditions::True, sStop);

      // Define entry action, activities, exit conditions, and exit actions
      sStop.AddActivity(behaviors::StopX);
      sStop.AddActivity(behaviors::StopY);
      sStop.AddActivity(behaviors::StopAngle);
      sStop.AddActivity(behaviors::StopCollectors);
      sStop.AddActivity(behaviors::StopScorer);

      // Start running the state machine
      StateMachine::Start(s1);
    }
  }
}