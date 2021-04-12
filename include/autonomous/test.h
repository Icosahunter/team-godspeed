#pragma once
#include "vex.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  namespace AutoTest
  {
    void ent1()
    {
      DO_FOR(behaviors::MoveBackward, 500);
      DO_FOR(behaviors::StopY, 500);
    }

    void ent3()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);

      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);

      DO_FOR(behaviors::MoveForward, 1800);
      DO_FOR(behaviors::StopY, 500);
      WAIT(800);

      Binder::RemoveBinding(behaviors::ScoreBall);
      Binder::RemoveBinding(behaviors::PickUpBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);

      DO_FOR(behaviors::MoveBackward, 500);
      DO_FOR(behaviors::StopY, 500);
    }

    void ent4()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      Binder::AddBinding(behaviors::ScoreBall);
      DO_FOR(behaviors::MoveForward, 1080);
      DO_FOR(behaviors::StopY, 500);
      WAIT(2500);
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
      static State sStop;

      s1.AddEntryAction(ent1);
      s1.AddActivity(behaviors::AlignWithBall);
      s1.AddTransition(conditions::AlignedWithBall, s2);

      s2.AddActivity(behaviors::AlignWithBall);
      s2.AddActivity(behaviors::MoveForward);
      s2.AddTransition(conditions::NearBall, s3);

      s3.AddEntryAction(ent3);
      s3.AddActivity(behaviors::AlignWithGoal);
      s3.AddActivity(behaviors::MoveForward);
      s3.AddTransition(conditions::NearGoal, s4);

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