#pragma once
#include "vex.h"
#define elem(l, i) *std::next(l.begin(), i)

namespace godspeed
{
  class Binding
  {
    public:

    double(*source)(void);
    double(*pipe)(double);
    void(*sink)(double);

    Binding(double(*src)(void), double(*pip)(double), void(*snk)(double))
    {
      source = src;
      pipe = pip;
      sink = snk;
    }

    Binding(double(*src)(void), void(*snk)(double))
    {
      source = src;
      pipe = nullptr;
      sink = snk;
    }

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
    
    bool kill = false;

    void AddBinding(Binding &b)
    {
      bindings.push_back(&b);
    }

    void SetBindings(std::list<Binding*> &l)
    {
      bindings.assign(l.begin(), l.end());
    }

    void ClearBindings()
    {
      bindings.clear();
    }

    void RemoveBinding(Binding &b)
    {
      bindings.remove(&b);
    }

    /// \brief calls all bindings that are not disabled. This does NOT need to be called manually.
    void Update()
    {
      while (!kill)
      {
        for(auto& x : bindings)
        {
          x->Update();
        }
        this_thread::yield();
      }
    }

    void Kill()
    {
      kill = true;
    }

    /// \brief Runs the binder update function on it's own thread
    void Init()
    {
      kill = false;
      thread t(Update);
      t.detach();
    }
  }
}