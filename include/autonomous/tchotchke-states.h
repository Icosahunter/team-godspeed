#pragma once
#include "vex.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  namespace Tchotchke
  {
    void ent1()
    {
      // Get into position
      DO_FOR(behaviors::MoveForward, 2500);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2200);
      DO_FOR(behaviors::StopAngle, 500);
    }

    void ent2()
    {
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach goal
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1200);
      // Finish scoring
      DO_FOR(behaviors::StopY, 600);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
      // Backup from current goal
      DO_FOR(behaviors::MoveBackward, 2300);
      // Turn toward other goal
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 1450);
    }

    void ent3()
    {
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach goal
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1100);
      // Back up a little while picking up ball
      Binder::AddBinding(behaviors::PickUpBall);
      DO_FOR(behaviors::MoveBackward, 800);
      Binder::RemoveBinding(behaviors::PickUpBall);
      outputs::BallCollector::TreadSpeed(0);
      // Score the ball
      DO_FOR(behaviors::MoveForward, 1000);
      DO_FOR(behaviors::StopY, 2500);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
      // Back up to collect next ball
      DO_FOR(behaviors::MoveBackward, 1500);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2100);
    }

    void ent4()
    {
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);

      DO_FOR(behaviors::MoveForward, 1400);
      DO_FOR(behaviors::StopY, 500);

      DO_FOR(behaviors::MoveBackward, 1000);

      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);

      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 1000);

      DO_FOR(behaviors::MoveForward, 1500);
      Binder::AddBinding(behaviors::ScoreBall);
      DO_FOR(behaviors::MoveForward, 1000);
      DO_FOR(behaviors::StopY, 1000);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
    }

    double expander_pos() { return 365; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);

    void StartAutonomous()
    {
      inputs::VisionSensor::XOffsetFudge = 0.35;
      inputs::BallStorage::BallCounter = 1;
      Binder::AddBinding(ExpanderBinding);

      static State s1;
      static State s2;
      static State s3;
      static State s4;
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
      s3.AddActivity(behaviors::AlignWithBall);
      s3.AddActivity(behaviors::MoveForward);
      s3.AddTransition(conditions::NearBall, s4);

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