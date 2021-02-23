#pragma once
#include "vex.h"
#include "autonomous/behavior-manager.h"
#include "autonomous/conditions.h"
#include "autonomous/behaviors.h"

namespace godspeed
{
  void LoadBehaviorStack()
  {
    
    // Tier 0
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(0, conditions::NearObstacle);
    BehaviorManager::AddBehavior(0, behaviors::AvoidObstacleBehavior());

    // Tier 1
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(1, conditions::BallLoaded);
    BehaviorManager::AddCondition(1, conditions::NearGoal);
    BehaviorManager::AddCondition(1, conditions::AlignedWithGoal);
    BehaviorManager::AddBehavior(1, behaviors::ScoreBallBehavior());

    // Tier 2
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(2, conditions::BallLoaded);
    BehaviorManager::AddCondition(2, conditions::NearGoal);
    BehaviorManager::AddBehavior(2, behaviors::AlignWithGoalBehavior());

    // Tier 3
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(3, conditions::BallLoaded);
    BehaviorManager::AddCondition(3, conditions::GoalTargeted);
    BehaviorManager::AddBehavior(3, behaviors::MoveForwardBehavior());
    BehaviorManager::AddBehavior(3, behaviors::AlignWithGoalBehavior());

    // Tier 4
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(4, conditions::BallLoaded);
    BehaviorManager::AddBehavior(4, behaviors::LocateObjectBehavior());

    // Tier 5
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(5, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(5, conditions::NearBall);
    BehaviorManager::AddCondition(5, conditions::AlignedWithBall);
    BehaviorManager::AddBehavior(5, behaviors::PickUpBallBehavior());

    // Tier 6
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(6, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(6, conditions::NearBall);
    BehaviorManager::AddBehavior(6, behaviors::AlignWithBallBehavior());

    // Tier 7
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(7, conditions::BallNotLoaded);
    BehaviorManager::AddCondition(7, conditions::BallTargeted);
    BehaviorManager::AddBehavior(7, behaviors::MoveForwardBehavior());
    BehaviorManager::AddBehavior(7, behaviors::AlignWithBallBehavior());

    // Tier 8
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(8, conditions::BallNotLoaded);
    BehaviorManager::AddBehavior(8, behaviors::LocateObjectBehavior());

    // Tier 9
    BehaviorManager::AddTier();
    BehaviorManager::AddCondition(9, conditions::True);
    BehaviorManager::AddBehavior(9, behaviors::WanderBehavior());
  }
}