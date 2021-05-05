#pragma once
#include "vex.h"

namespace godspeed
{
  /// \brief A class that represents a binding between two functions
  class Binding
  {
    public:

    double(*source)(void);
    double(*pipe)(double);
    void(*sink)(double);

    /// \brief Constructor that accepts a source, pipe, and sink function
    Binding(double(*src)(void), double(*pip)(double), void(*snk)(double))
    {
      source = src;
      pipe = pip;
      sink = snk;
    }

    /// \brief Constructor that accepts a source and sink function
    Binding(double(*src)(void), void(*snk)(double))
    {
      source = src;
      pipe = nullptr;
      sink = snk;
    }

    /// \brief Update the binding
    void Update()
    {
      if (pipe != nullptr)
      {
        sink(pipe(source()));
      }
      else
      {
        sink(source());
      }
    }
  };

  /**
  * \brief A namespace containing functions for binding value producing functions to value consuming functions
  *
  * There are 3 types of functions considered here, source functions which take no values
  * and return a double, pipe functions which take a double and return a double, and sink functions
  * which take a double and return nothing. Once the Binder is initialized, it will go through and 
  * repeatedly call the sink functions with the value produced by the source functions as the input. 
  */
  namespace Binder
  {
    /// \brief A list of bindings
    std::list<Binding*> bindings = std::list<Binding*>();
    thread* tptr;

    /// \brief Add a binding to the binder
    void AddBinding(Binding &b)
    {
      if (!contains(bindings, &b))
      {
        bindings.push_back(&b);
      }
    }

    /// \brief Set the bindings list (overwrites current binding list)
    void SetBindings(std::list<Binding*> &l)
    {
      bindings.assign(l.begin(), l.end());
    }

    /// \brief Remove all current bindings
    void ClearBindings()
    {
      bindings.clear();
    }

    /// \brief Remove given binding from the update list
    void RemoveBinding(Binding &b)
    {
      if (contains(bindings, &b))
      {
        bindings.remove(&b);
      }
    }

    /// \brief Iterates through and updates all bindings. This does NOT need to be called manually.
    void Update()
    {
      while (true)
      {
        for(auto& x : bindings)
        {
            x->Update();
        }
        this_thread::yield();
      }
    }

    /// \brief Stops binder thread
    void Kill()
    {
      if (tptr != nullptr)
      {
        tptr->interrupt();
        tptr = nullptr;
      }
    }

    /// \brief Runs the binder update function on it's own thread
    void Init()
    {
      thread t(Update);
      tptr = &t;
      t.detach();
    }
  }
}