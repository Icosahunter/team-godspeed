#pragma once
#include "framework/binder.h"
#include <list>
#include <tuple>
#include "vex.h"

#define CONDITION bool(*)(void)
#define ACTION void(*)(void)
#define TRANSITION std::tuple<CONDITION, State*>

namespace godspeed
{
  class State
  {
    public:

    std::list<ACTION> entryActions;
    std::list<ACTION> exitActions;
    std::list<TRANSITION> transitions;
    std::list<Binding*> activities;

    void AddTransition(bool(*condition)(void), State &state)
    {
      transitions.push_back(TRANSITION(condition, &state));
    }

    void AddEntryAction(void(*action)(void))
    {
      entryActions.push_back(action);
    }

    void AddExitAction(void(*action)(void))
    {
      exitActions.push_back(action);
    }

    void AddActivity(Binding &activity)
    {
      activities.push_back(&activity);
    }
  };

  namespace StateMachine
  {
    State* currentState;

    void ChangeState(State &state)
    {
      for(auto& b : currentState->activities)
      {
        Binder::RemoveBinding(*b);
      }
      for(auto&a : currentState->exitActions)
      {
        a();
      }
      
      currentState = &state;

      for(auto& a : currentState->entryActions)
      {
        a();
      }
      for(auto& b : currentState->activities)
      {
        Binder::AddBinding(*b);
      }
    }

    /// \brief Update function called by the State Machine thread
    void Update()
    {
      bool stateChanged = false;
      State* cur;

      while (true)
      {
        cur = currentState;
        for(auto const &t : cur->transitions)
        {
          if (std::get<0>(t)())
          {
            ChangeState(*std::get<1>(t));
            break;
          }
        }
        this_thread::yield();
      }
    }

    void Start(State &starting_state)
    {
      currentState = &starting_state;
      for(auto& a : currentState->entryActions)
      {
        a();
      }
      for(auto& b : currentState->activities)
      {
        Binder::AddBinding(*b);
      }
    }

    /// \brief Runs the state machine update function on it's own thread
    void Init()
    {
      thread t(Update);
      t.detach();
    }
  };
}