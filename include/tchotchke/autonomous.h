#pragma once
#include "vex.h"
#include "tchotchke.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  namespace Tchotchke
  {
    /// \brief Condition for if the center line ball is close enough that it probably hasn't been moved by opponent robots or anything
    bool CenterLineBallNotFound()
    {
      if (inputs::VisionSensor::BallDistance() > 100)
      {
        return true;
      }
      else 
      {
        return false;
      }
    }

    /// \brief Entry action for state 1
    void ent1()
    {
      // Get into position
      Binder::AddBinding(behaviors::PickUpBall);
      DO_FOR(behaviors::MoveForward, 2800);
      Binder::RemoveBinding(behaviors::PickUpBall);
      outputs::BallCollector::TreadSpeed(0);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2350);
      DO_FOR(behaviors::StopAngle, 500);
    }

    /// \brief Entry action for state 2
    void ent2()
    {
      inputs::VisionSensor::GoalDistVar.Initialize(infinity());
      // Approach goal
      DO_FOR(behaviors::TurnLeft, 35);
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      Binder::AddBinding(behaviors::ScoreBall);
      WAIT(1350);
      // Finish scoring
      DO_FOR(behaviors::StopY, 1500);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
      // Backup from current goal
      DO_FOR(behaviors::MoveBackward, 2300);
      // Turn toward other goal
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 1450);
      inputs::VisionSensor::XOffsetFudge = 0.15;
    }

    /// \brief Entry action for state 3
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
      DO_FOR(behaviors::MoveBackward, 1150);
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);
      DO_FOR(behaviors::StopY, 500);
    }

    /// \brief Entry action for state 5
    void ent5()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      // Score the ball
      Binder::AddBinding(behaviors::ScoreBall);
      DO_FOR(behaviors::MoveForward, 1500);
      DO_FOR(behaviors::StopY, 2500);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallScorer::TreadSpeed(0);
      // Back up to collect next ball
      DO_FOR(behaviors::MoveBackward, 1200);
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 2400);
      inputs::VisionSensor::BallDistanceScan();
    }

    /// \brief Entry action for state 7
    void ent7()
    {
      outputs::OmniDrive3Wheel::AngleSpeed(0);
      Binder::AddBinding(behaviors::PickUpBall);
      Binder::AddBinding(behaviors::ScoreBall);

      DO_FOR(behaviors::MoveForward, 1500);
      DO_FOR(behaviors::StopY, 500);

      DO_FOR(behaviors::MoveBackward, 1000);
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);
      DO_FOR(behaviors::MoveBackward, 700);
    }

    /// \brief Entry action for state 8
    void ent8()
    {
      DO_FOR(behaviors::StopY, 500);
      DO_FOR(behaviors::TurnRight, 760);
      outputs::OmniDrive3Wheel::AngleSpeed(0);

      DO_FOR(behaviors::MoveForward, 500);

      Binder::AddBinding(behaviors::ScoreBall);
      Binder::AddBinding(behaviors::PickUpBall);
      DO_FOR(behaviors::MoveForward, 2500);

      DO_FOR(behaviors::StopY, 3000);
      Binder::RemoveBinding(behaviors::PickUpBall);
      Binder::RemoveBinding(behaviors::ScoreBall);
      outputs::BallCollector::TreadSpeed(0);
      outputs::BallScorer::TreadSpeed(0);

      DO_FOR(behaviors::MoveBackward, 800);
      DO_FOR(behaviors::StopY, 500);
    }

    /// \brief Start Tchotchke autonomous routine
    void StartAutonomous()
    {
      conditions::nearGoalThreshold = 30;
      conditions::nearBallThreshold = 30; //28
      inputs::VisionSensor::XOffsetFudge = 0.35;
      inputs::BallStorage::BallCounter = 1;
      behaviors::AlignAgression = 1.8;
      Binder::AddBinding(ExpanderBinding);
      outputs::OmniDrive3Wheel::SaturationEnabled = false;

      static State s1;
      static State s2;
      static State s3;
      static State s4;
      static State s5;
      static State s6;
      static State s7;
      static State s8;
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
      s3.AddTransition(conditions::BallLoaded, s4);
      s3.AddTransition(conditions::BallNotLoaded, sStop);

      s4.AddActivity(behaviors::AlignWithGoal);
      s4.AddActivity(behaviors::MoveForward);
      s4.AddTransition(conditions::NearGoal, s5);

      s5.AddEntryAction(ent5);
      s5.AddActivity(behaviors::AlignWithBall);
      s5.AddTransition(CenterLineBallNotFound, sStop);
      s5.AddTransition(conditions::AlignedWithBall, s6);

      s6.AddActivity(behaviors::AlignWithBall);
      s6.AddActivity(behaviors::MoveForward);
      s6.AddTransition(conditions::NearBall, s7);

      s7.AddEntryAction(ent7);
      s7.AddTransition(conditions::BallNotLoaded, sStop);
      s7.AddTransition(conditions::BallLoaded, s8);

      s8.AddEntryAction(ent8);
      s8.AddTransition(conditions::True, sStop);

      sStop.AddActivity(behaviors::StopX);
      sStop.AddActivity(behaviors::StopY);
      sStop.AddActivity(behaviors::StopAngle);
      sStop.AddActivity(behaviors::StopCollectors);
      sStop.AddActivity(behaviors::StopScorer);

      StateMachine::Start(s1);
    }
  }
}