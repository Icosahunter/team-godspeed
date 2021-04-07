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

    // Define lists to set up each state with its behaviors
    // List to track what actions to execute when the state is entered
    std::list<ACTION> entryActions;
    // List to track what actions to execute when the state is exited
    std::list<ACTION> exitActions;
    // List to track the conditions needed to enter another state
    std::list<TRANSITION> transitions;
    // List to track the activities that will be active when in the state
    std::list<Binding*> activities;

    // Add a transition condition to the state's list
    void AddTransition(bool(*condition)(void), State &state)
    {
      transitions.push_back(TRANSITION(condition, &state));
    }

    // Add an entry action to the state's list
    void AddEntryAction(void(*action)(void))
    {
      entryActions.push_back(action);
    }

    // Add an exit action to the state's list
    void AddExitAction(void(*action)(void))
    {
      exitActions.push_back(action);
    }

    // Add an activity to the state's list
    void AddActivity(Binding &activity)
    {
      activities.push_back(&activity);
    }
  };

  namespace StateMachine
  {
    // Reference to the active state
    State* currentState;

    // Handle the transition between states (execute exit actions, entry actions)
    void ChangeState(State &state)
    {
      // Stop executing activities of the active state
      for(auto& b : currentState->activities)
      {
        Binder::RemoveBinding(*b);
      }

      // Execute exit actions
      for(auto&a : currentState->exitActions)
      {
        a();
      }
      
      // Set the next state as the active state
      currentState = &state;

      // Execute entry actions
      for(auto& a : currentState->entryActions)
      {
        a();
      }

      // Execute activities of the newly activated state
      for(auto& b : currentState->activities)
      {
        Binder::AddBinding(*b);
      }
    }

    /// \brief Update function called by the State Machine thread
    void Update()
    {
      // Track whether the state has changed
      bool stateChanged = false;
      // Reference to the current active state
      State* cur;

      while (true)
      {
        // If the current active state changed since the last time
        // through the loop, update it
        cur = currentState;
        
        // Check the conditions for each transition to see if any are met.
        // If one is, make the transition
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

    // Handle entering the first state
    void Start(State &starting_state)
    {
      // Set the first state to the current active state
      currentState = &starting_state;

      // Handle entry actions
      for(auto& a : currentState->entryActions)
      {
        a();
      }

      // Start activities
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