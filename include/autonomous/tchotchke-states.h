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
      DO_FOR(behaviors::MoveForward, 2700);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2350);
      DO_FOR(behaviors::StopAngle, 500);
    }

    void ent2()
    {
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach goal
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1080);
      // Finish scoring
      DO_FOR(behaviors::StopY, 1000);
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
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach ball
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1900);
      // Pickup ball
      DO_FOR(behaviors::StopY, 1000);
      DO_FOR(behaviors::MoveBackward, 1200);
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);
      DO_FOR(behaviors::StopY, 500);
    }
    
    void ent4()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      // Score the ball
      Binder::AddBinding(behaviors::ScoreBall);
      DO_FOR(behaviors::MoveForward, 1080);
      DO_FOR(behaviors::StopY, 2500);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
      // Back up to collect next ball
      DO_FOR(behaviors::MoveBackward, 1100);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2400);
    }

    void ent6()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);

      DO_FOR(behaviors::MoveForward, 3000);
      DO_FOR(behaviors::StopY, 500);

      DO_FOR(behaviors::MoveBackward, 1300);

      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);

      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 800);
      outputs::OmniDrive3Wheel::AngleSpeed(0);

      DO_FOR(behaviors::MoveForward, 1700);
      Binder::AddBinding(behaviors::ScoreBall);
      Binder::AddBinding(behaviors::PickUpBall);
      DO_FOR(behaviors::MoveForward, 1300);

      DO_FOR(behaviors::StopY, 3000);
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);

      DO_FOR(behaviors::MoveBackward, 300);
      DO_FOR(behaviors::StopY, 500);
    }

    double expander_pos() { return 355; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);

    void StartAutonomous()
    {
      conditions::nearGoalThreshold = 28;
      conditions::nearBallThreshold = 28;
      inputs::VisionSensor::XOffsetFudge = 0.25;
      inputs::BallStorage::BallCounter = 1;
      behaviors::AlignAgression = 1.8;
      Binder::AddBinding(ExpanderBinding);

      static State s1;
      static State s2;
      static State s3;
      static State s4;
      static State s5;
      static State s6;
      static State sStop;

      s1.AddEntryAction(ent1);
      s1.AddActivity(behaviors::AlignWithGoal);
      s1.AddActivity(behaviors::MoveForward);
      s1.AddTransition(conditions::NearGoal, s2);

      s2.AddEntryAction(ent2);
      s2.AddActivity(behaviors::AlignWithBall);
      s2.AddActivity(behaviors::MoveForward);
      s2.AddTransition(conditions::NearBall, s3);

      s3.AddEntryAction(ent3);
      s3.AddActivity(behaviors::AlignWithGoal);
      s3.AddActivity(behaviors::MoveForward);
      s3.AddTransition(conditions::NearGoal, s4);

      s4.AddEntryAction(ent4);
      s4.AddActivity(behaviors::AlignWithBall);
      s4.AddTransition(conditions::AlignedWithBall, s5);

      s5.AddActivity(behaviors::AlignWithBall);
      s5.AddActivity(behaviors::MoveForward);
      s5.AddTransition(conditions::NearBall, s6);

      s6.AddEntryAction(ent6);
      s6.AddTransition(conditions::True, sStop);

      sStop.AddActivity(behaviors::StopX);
      sStop.AddActivity(behaviors::StopY);
      sStop.AddActivity(behaviors::StopAngle);
      sStop.AddActivity(behaviors::StopCollectors);
      sStop.AddActivity(behaviors::StopScorer);

      StateMachine::Start(s1);
    }
  }
}