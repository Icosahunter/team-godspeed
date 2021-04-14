#pragma once
#include "vex.h"
#include "bauble.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  namespace Bauble
  {
    void ent1()
    {
      // Get into position
      DO_FOR(behaviors::MoveForward, 2700);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2150);
      DO_FOR(behaviors::StopAngle, 500);
    }

    void ent2()
    {
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach goal
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1200);
      // Finish scoring
      DO_FOR(behaviors::StopY, 1000);
      // Finish picking up ball
      Binder::AddBinding(behaviors::PickUpBall);
      DO_FOR(behaviors::MoveBackward, 2900);
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);
      // Move to other goal
      DO_FOR(behaviors::StopY, 450);
      DO_FOR(behaviors::TurnLeft, 2000);
    }

    void ent3()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach goal
      WAIT(550);
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::MoveForward);
      Binder::AddBinding(behaviors::TurnLeft);
      WAIT(500);
      Binder::RemoveBinding(behaviors::MoveForward);
      Binder::AddBinding(behaviors::StopY);
      WAIT(1500);
      Binder::RemoveBinding(behaviors::TurnLeft);
      Binder::RemoveBinding(behaviors::StopY);
      Binder::RemoveBinding(behaviors::PickUpBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      // DO_FOR(behaviors::MoveBackward, 800);
      // DO_FOR(behaviors::StopY, 500);
      // DO_FOR(behaviors::TurnRight, 2000);
      // outputs::OmniDrive3Wheel::AngleSpeed(0);
      // DO_FOR(behaviors::MoveBackward, 2000);
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

    void StartAutonomous()
    {
      conditions::nearGoalThreshold = 28;
      conditions::nearBallThreshold = 30;
      inputs::VisionSensor::XOffsetFudge = 0;
      inputs::BallStorage::BallCounter = 1;
      behaviors::AlignAgression = 1;
      Binder::AddBinding(ExpanderBinding);

      static State s1;
      static State s2;
      static State s3;
      static State s4;
      static State s5;
      static State sStop;

      s1.AddEntryAction(ent1);
      s1.AddActivity(behaviors::AlignWithGoal);
      s1.AddActivity(behaviors::MoveForward);
      s1.AddTransition(conditions::NearGoal, s2);

      s2.AddEntryAction(ent2);
      s2.AddActivity(behaviors::AlignWithGoal);
      s2.AddActivity(behaviors::MoveForward);
      s2.AddTransition(conditions::NearGoal, s3);

      s3.AddEntryAction(ent3);
      s3.AddActivity(behaviors::AlignWithGoal);
      s3.AddActivity(behaviors::MoveForward);
      s3.AddTransition(conditions::True, sStop);
      //s3.AddTransition(conditions::NearGoal, s4);

      s4.AddEntryAction(ent4);
      s4.AddTransition(conditions::True, sStop);

      sStop.AddActivity(behaviors::StopX);
      sStop.AddActivity(behaviors::StopY);
      sStop.AddActivity(behaviors::StopAngle);
      sStop.AddActivity(behaviors::StopCollectors);
      sStop.AddActivity(behaviors::StopScorer);

      StateMachine::Start(s1);
    }
  }
}