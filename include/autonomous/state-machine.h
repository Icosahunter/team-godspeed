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
  /// \brief A state class used to create statemachines to execute using the StateMachine namespace
  class State
  {
    public:

    std::list<ACTION> entryActions;
    std::list<ACTION> exitActions;
    std::list<TRANSITION> transitions;
    std::list<Binding*> activities;

    /// \brief Add a transition to the state
    void AddTransition(bool(*condition)(void), State &state)
    {
      transitions.push_back(TRANSITION(condition, &state));
    }

    /// \brief Add an entry action to the state
    void AddEntryAction(void(*action)(void))
    {
      entryActions.push_back(action);
    }

    /// \brief Add an exit action to the state
    void AddExitAction(void(*action)(void))
    {
      exitActions.push_back(action);
    }

    /// \brief Add an activity (binding) to the state
    void AddActivity(Binding &activity)
    {
      activities.push_back(&activity);
    }
  };

  /// \brief A namespace for executing a state machine
  namespace StateMachine
  {
    State* currentState;
    thread* tptr;
    bool kill = false;

    /// \brief Changes the state of the state machine, performs entry and exit actions and handles activity enabling and disabling
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

      while (!kill)
      {
        cur = currentState;
        for(auto const &t : cur->transitions)
        {
          if (kill)
          {
            break;
          }
          if (std::get<0>(t)())
          {
            ChangeState(*std::get<1>(t));
            break;
          }
        }
        this_thread::yield();
      }
      this_thread::yield();
    }

    /// \brief Starts executing a state machine given the initial state
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

    /// \brief A function to stop the state machine thread
    void Kill()
    {
      kill = true;
      // if (tptr != nullptr)
      // {
      //   tptr->interrupt();
      //   tptr = nullptr;
      // }
    }

    /// \brief Runs the state machine update function on it's own thread
    void Init()
    {
      kill = false;
      thread t(Update);
      tptr = &t;
      t.detach();
    }
  };
}