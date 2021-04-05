#pragma once
#include "vex.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  void ea1()
  {
    DO_FOR(behaviors::MoveForward, 2700);
    DO_FOR(behaviors::StopY, 500);
    DO_FOR(behaviors::TurnRight, 2150);
    DO_FOR(behaviors::StopAngle, 500);
  }

  void ea2()
  {
    Binder::AddBinding(behaviors::PickUpBall);
    Binder::AddBinding(behaviors::ScoreBall);
    WAIT(600);
    Binder::AddBinding(behaviors::StopY);
  }

  void ea3()
  {
    DO_FOR(behaviors::MoveBackward, 1000);
  }

  void ea4()
  {
    DO_FOR(behaviors::MoveBackward, 3000);
    DO_FOR(behaviors::TurnLeft, 2000);
  }

  double expander_pos() { return 355; }
  Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);

  void LoadStatesTest()
  {
    inputs::BallStorage::BallCounter = 1;
    Binder::AddBinding(ExpanderBinding);

    static State s1;
    static State s2;
    static State s3;
    static State s4;
    static State sStop;

    s1.AddEntryAction(ea1);
    s1.AddActivity(behaviors::AlignWithGoal);
    s1.AddActivity(behaviors::MoveForward);
    s1.AddTransition(conditions::NearGoal, s2);

    s2.AddEntryAction(ea2);
    s2.AddTransition(conditions::BallNotLoaded, sStop);

    s3.AddEntryAction(ea3);
    s3.AddTransition(conditions::BallLoaded, s4);

    s4.AddEntryAction(ea4);
    s4.AddTransition(conditions::True, sStop);

    sStop.AddActivity(behaviors::StopX);
    sStop.AddActivity(behaviors::StopY);
    sStop.AddActivity(behaviors::StopAngle);
    sStop.AddActivity(behaviors::StopCollectors);
    sStop.AddActivity(behaviors::StopScorer);

    StateMachine::Start(s1);
  }
}