#pragma once
#include "framework/binder.h"
#include <list>
#include <tuple>
#include "vex.h"
#define CONDITION bool(*)(void)
#define ACTION void(*)(void)
#define TRANSITION std::tuple<CONDITION, State*>
#define ACTIVITY Binding

namespace godspeed
{
  class State
  {
    public:

    std::list<ACTION> entryActions;
    std::list<TRANSITION> transitions;
    std::list<ACTIVITY> activities;

    void AddTransition(bool(*condition)(void), State &state)
    {
      transitions.push_back(TRANSITION(condition, &state));
    }

    void AddEntryAction(void(*action)(void))
    {
      entryActions.push_back(action);
    }

    void AddActivity(ACTIVITY activity)
    {
      activities.push_back(activity);
    }
  };

  namespace StateMachine
  {
    State* currentState;

    std::list<State> states;

    void AddState(State &state)
    {
      states.push_back(state);
    }

    void ChangeState(State &state)
    {
      Binder::ClearBindings();
      currentState = &state;
      for(auto& a : state.entryActions)
      {
        a();
      }
      Binder::SetBindings(state.activities);
    }

    /// \brief Update function called by the Behavior Manager thread
    void Update()
    {
      bool stateChanged = false;
      while (true)
      {
        State* cur = currentState;
        for(auto& t : cur->transitions)
        {
          if (std::get<0>(t)())
          {
            ChangeState(*std::get<1>(t));
            break;
          }
        }
      }
    }

    /// \brief Runs the binder update function on it's own thread
    void Init()
    {
      thread t(Update);
      t.detach();
    }
  };
}