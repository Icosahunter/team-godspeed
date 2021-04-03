#pragma once
#include "vex.h"
#include <list>

namespace godspeed
{
  namespace Control
  {
    std::list<void(*)(void)> tasks;
    
    void AddTask(void(*t)(void))
    {
      tasks.push_back(t);
    }

    void Start()
    {
      while (true)
      {
        for (auto &t : tasks)
        {
          t();
        }
      }
    }
  }
}