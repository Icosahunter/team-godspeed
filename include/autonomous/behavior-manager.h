#pragma once
#include "framework/binder.h"
#include "vex.h"

#define BEHAVIOR_TUPLE std::tuple<int, int> // tier, behavior id

#define tier(x) std::get<0>(x)
#define cond(x) std::get<1>(x)
#define beh(x) std::get<1>(x)

namespace godspeed
{
  /// \brief A namespace containing functions and logic for managing autonomous behaviors
  namespace BehaviorManager
  {
    std::list<std::list<bool(*)(void)>> conditions = std::list<std::list<bool(*)(void)>>();   
    std::list<BEHAVIOR_TUPLE> behaviors = std::list<BEHAVIOR_TUPLE>();

    /// \brief Add a tier and return the ID of the tier created
    int AddTier()
    {
      conditions.push_back(std::list<bool(*)(void)>());
      return conditions.size() - 1;
    }

    /// \brief Add a number of tiers
    void AddTiers(int num)
    {
      for (int i=0; i<num; i++)
      {
        conditions.push_back(std::list<bool(*)(void)>());
      }
    }

    /// \brief Add a behavior
    void AddBehavior(int tier, int binding_id)
    {
      behaviors.push_back(BEHAVIOR_TUPLE(tier, binding_id));
    }

    /// \brief Add a condition
    void AddCondition(int tier, bool(*condition)(void))
    {
      if (conditions.size() > tier)
      {
        elementAt(conditions, tier).push_back(condition);
      }
    }

    /// \brief Update function called by the Behavior Manager thread
    void Update()
    {
      while (true)
      {
        int t = 0;

        for(auto& x : conditions) //Find tier where all it's conditions are met
        {
          bool v = true;
          for (auto&y : x)
          {
            v = v && y();
          }

          if (v) { break; }
          
          t++; 
        }

        for(auto& x: behaviors) //Activate all behaviors in the active tier, and disable all those that are not
        {
          if (tier(x) == t)
          {
            Binder::Enable(beh(x));
          }
          else
          {
            Binder::Disable(beh(x));
          }
        }
      }
    }

    /// \brief Run the Behavior Manager on it's own thread
    void Init()
    {
      thread t(Update);
      t.detach();
    }
  }
}