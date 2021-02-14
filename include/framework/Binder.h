#pragma once
#include "vex.h"
#include <list>
#include <tuple>
#include <algorithm>
#define BINDING_TUPLE std::tuple<int, double(*)(void), double(*)(double), void(*)(double)>

namespace godspeed
{
  /**
  * \brief A namespace containing functions for binding value producing functions to value consuming functions
  *
  * There are 3 types of functions considered here, source functions which take no values
  * and return a double, pipe functions which take a double and return a double, and sink functions
  * which take a double and return nothing. The Bind function allows you to bind the output of a 
  * source function to a sink function (optionally through a pipe function). Then, once the Binder
  * is initialized, it will go through and repeatedly call the sink functions with the value produced 
  * by the source functions as the input. 
  */
  namespace Binder
  {
    /// \brief A list of tuples. Each tuple represents a binding.
    std::list<BINDING_TUPLE> bindings = std::list<BINDING_TUPLE>();

    /// \brief A list of disabled binding IDs
    std::list<int> disabled = std::list<int>();

    /// \brief Runs the binder update function on it's own thread
    void Init()
    {
      thread(Update);
    }

    /// \brief Bind a source function to a sink function
    int Bind(double(*source)(void), void(*sink)(double))
    {
      int id = bindings.size();
      bindings.push_back(BINDING_TUPLE(id, source, nullptr, sink));
      return id;
    }

    /// \brief Bind a source function to a sink function through a pipe function
    int Bind(double(*source)(void), double(*pipe)(double), void(*sink)(double))
    {
      int id = bindings.size();
      bindings.push_back(BINDING_TUPLE(id, source, pipe, sink));
      return id;
    }

    /// \brief Disable a binding using the bindings ID
    void DisableBinding(int id)
    {
      disabled.push_back(id);
    }

    /// \brief Check if a binding is disabled using the bindings ID
    bool IsDisabled(int id)
    {
      return std::find(disabled.begin(), disabled.end(), id) != disabled.end();
    }

    /// \brief calls all bindings that are not disabled. This does NOT need to be called manually.
    void Update()
    {
      while (true)
      {
        for(auto& x : bindings)
        {
          if (!IsDisabled(std::get<0>(x)))
          {
            if (std::get<2>(x) == nullptr)
            {
              std::get<3>(x)(std::get<1>(x)());
            }
            else
            {
              std::get<3>(x)(std::get<2>(x)(std::get<1>(x)()));
            }
          }
        }
      }
    }
  }
}