#pragma once
#include "vex.h"
#include <list>
#include <tuple>
#define BINDING_TUPLE std::tuple<int, double(*)(void), double(*)(double), void(*)(double)>

namespace godspeed
{
  namespace Binder
  {
    std::list<BINDING_TUPLE> bindings = std::list<BINDING_TUPLE>();

    void Init()
    {
      thread(Update);
    }

    int Bind(double(*source)(void), void(*sink)(double))
    {
      int id = bindings.size();
      bindings.push_back(BINDING_TUPLE(id, source, nullptr, sink));
      return id;
    }

    int Bind(double(*source)(void), double(*pipe)(double), void(*sink)(double))
    {
      int id = bindings.size();
      bindings.push_back(BINDING_TUPLE(id, source, pipe, sink));
      return id;
    }

    void Update()
    {
      for(auto& x : bindings)
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