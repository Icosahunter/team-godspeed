#pragma once
#include "vex.h"
#include "autonomous/behavior-manager.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

namespace godspeed
{
  /// \brief Loads the tiers, behaviors, and conditions for an autonomous test [FOR TESTING AND DEBUGGING]
  void LoadBehaviorTest()
  {
    int t;

    // t = BehaviorManager::AddTier();
    // BehaviorManager::AddCondition(t, conditions::NearObstacle);
    // BehaviorManager::AddBehavior(t, behaviors::AvoidObstacle());
    // BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Score goal
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::GoalCaught);
    BehaviorManager::AddCondition(t, conditions::BallLoaded);
    BehaviorManager::AddBehavior(t, behaviors::ScoreBall());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopY());
    BehaviorManager::AddBehavior(t, behaviors::StopTurn());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Catch goal
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::NearGoal);
    BehaviorManager::AddCondition(t, conditions::BallLoaded);
    BehaviorManager::AddBehavior(t, behaviors::MoveForward());
    BehaviorManager::AddBehavior(t, behaviors::ScoreBall());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopTurn());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Move toward goal
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::BallLoaded);
    BehaviorManager::AddCondition(t, conditions::GoalTargeted);
    BehaviorManager::AddBehavior(t, behaviors::AlignWithGoal());
    BehaviorManager::AddBehavior(t, behaviors::MoveForward());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopScorer());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Locate goal
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::BallLoaded);
    BehaviorManager::AddBehavior(t, behaviors::LocateObject());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopY());
    BehaviorManager::AddBehavior(t, behaviors::StopScorer());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Load ball
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(t, conditions::BallCaught);
    BehaviorManager::AddBehavior(t, behaviors::PickUpBall());
    BehaviorManager::AddBehavior(t, behaviors::ScoreBall());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopY());
    BehaviorManager::AddBehavior(t, behaviors::StopTurn());

    //Catch ball
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(t, conditions::NearBall);
    BehaviorManager::AddBehavior(t, behaviors::PickUpBall());
    BehaviorManager::AddBehavior(t, behaviors::ScoreBall());
    BehaviorManager::AddBehavior(t, behaviors::MoveForward());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopTurn());

    //Move toward ball
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(t, conditions::BallTargeted);
    BehaviorManager::AddBehavior(t, behaviors::AlignWithBall());
    BehaviorManager::AddBehavior(t, behaviors::MoveForward());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopScorer());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Locate ball
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::BallNotLoaded);
    BehaviorManager::AddBehavior(t, behaviors::LocateObject());
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopY());
    BehaviorManager::AddBehavior(t, behaviors::StopScorer());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());

    //Stop
    t = BehaviorManager::AddTier();
    BehaviorManager::AddCondition(t, conditions::True);
    BehaviorManager::AddBehavior(t, behaviors::StopX());
    BehaviorManager::AddBehavior(t, behaviors::StopY());
    BehaviorManager::AddBehavior(t, behaviors::StopTurn());
    BehaviorManager::AddBehavior(t, behaviors::StopScorer());
    BehaviorManager::AddBehavior(t, behaviors::StopCollectors());
  }

  /// \brief Loads the tiers, behaviors, and conditions for autonomous mode [UNFINISHED]
  void LoadBehaviorStack()
  {
    
    // Tier 0
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(0, conditions::NearObstacle);
    BehaviorManager::AddBehavior(0, behaviors::AvoidObstacle());

    // Tier 1
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(1, conditions::BallLoaded);
    BehaviorManager::AddCondition(1, conditions::NearGoal);
    BehaviorManager::AddCondition(1, conditions::AlignedWithGoal);
    BehaviorManager::AddBehavior(1, behaviors::ScoreBall());

    // Tier 2
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(2, conditions::BallLoaded);
    BehaviorManager::AddCondition(2, conditions::NearGoal);
    BehaviorManager::AddBehavior(2, behaviors::AlignWithGoal());

    // Tier 3
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(3, conditions::BallLoaded);
    BehaviorManager::AddCondition(3, conditions::GoalTargeted);
    BehaviorManager::AddBehavior(3, behaviors::MoveForward());
    BehaviorManager::AddBehavior(3, behaviors::AlignWithGoal());

    // Tier 4
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(4, conditions::BallLoaded);
    BehaviorManager::AddBehavior(4, behaviors::LocateObject());

    // Tier 5
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(5, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(5, conditions::NearBall);
    BehaviorManager::AddCondition(5, conditions::AlignedWithBall);
    BehaviorManager::AddBehavior(5, behaviors::PickUpBall());

    // Tier 6
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(6, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(6, conditions::NearBall);
    BehaviorManager::AddBehavior(6, behaviors::AlignWithBall());

    // Tier 7
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(7, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(7, conditions::BallTargeted);
    BehaviorManager::AddBehavior(7, behaviors::MoveForward());
    BehaviorManager::AddBehavior(7, behaviors::AlignWithBall());

    // Tier 8
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(8, conditions::BallNotLoaded);
    BehaviorManager::AddBehavior(8, behaviors::LocateObject());

    // Tier 9
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(9, conditions::True);
    BehaviorManager::AddBehavior(9, behaviors::Wander());
  }
}