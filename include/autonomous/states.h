#pragma once
#include "vex.h"
#include "autonomous/state-machine.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

#define WAIT(t) task::sleep(t)
#define DO_FOR(b, t) Binder::AddBinding(b); WAIT(t); Binder::RemoveBinding(b);

namespace godspeed
{
  void A()
  {
    Brain.Screen.print("a");
    WAIT(500);
    Brain.Screen.print("b");
    Binder::AddBinding(behaviors::MoveForward); 
    Brain.Screen.print("c");
    WAIT(500);
    Binder::RemoveBinding(behaviors::MoveForward);
    WAIT(100);
    DO_FOR(behaviors::TurnLeft, 500);
  }

  void B()
  {
    outputs::BallCollector::TreadSpeed(1);
    outputs::BallScorer::TreadSpeed(1);
    Binder::AddBinding(behaviors::MoveForward);
    wait(350, msec);
    Binder::RemoveBinding(behaviors::MoveForward);
  }

  void C()
  {
    outputs::OmniDrive3Wheel::AngleSpeed(0);
    outputs::BallCollector::TreadSpeed(0);
    outputs::BallScorer::TreadSpeed(0);
  }

  void D()
  {
    Binder::AddBinding(behaviors::MoveBackward);
    wait(350, msec);
    Binder::RemoveBinding(behaviors::MoveBackward);
  }

  void LoadStatesTest()
  {
    inputs::BallStorage::BallCounter = 1;

    static State s1;
    static State s2;
    static State s3;

    s1.AddEntryAction(C);
    s1.AddEntryAction(A);
    s1.AddActivity(behaviors::AlignWithGoal);
    s1.AddActivity(behaviors::MoveForward);
    s1.AddTransition(conditions::NearGoal, s2);

    s2.AddEntryAction(C);
    s2.AddEntryAction(B);
    s2.AddTransition(conditions::BallNotLoaded, s3);

    s3.AddEntryAction(C);
    s3.AddEntryAction(D);

    StateMachine::Start(s1);
  }
}