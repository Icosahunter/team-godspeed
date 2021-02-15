#pragma once
#include "framework/binder.h"
#include "vex.h"

#define BEHAVIOR_TUPLE std::tuple<int, int> // tier, behavior id

#define tier(x) std::get<0>(x)
#define cond(x) std::get<1>(x)
#define beh(x) std::get<1>(x)

namespace godspeed
{
  namespace BehaviorManager
  {
    std::list<std::list<double(*)(void)>> conditions = std::list<std::list<double(*)(void)>>();   
    std::list<BEHAVIOR_TUPLE> behaviors = std::list<BEHAVIOR_TUPLE>();    

    void Init()
    {
      thread(Update);
    }

    void AddBehavior(int tier, int binding_id)
    {
      behaviors.push_back(BEHAVIOR_TUPLE(tier, binding_id));
    }

    void AddCondition(int tier, double(*condition)(void))
    {
      if (conditions.size() > tier)
      {
        elementAt(conditions, tier).push_back(condition);
      }
    }

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
  }
}