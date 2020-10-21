#pragma once
#include "vex.h"
#include <map>

namespace godspeed
{
  class Event
  {
    public:
      Event();
      void raise();
      Event addHandler(void (*handler)(void));
      Event removeHandler(void (*handler)(void));
    
    private:
      std::map <void (*)(void), void*> handlers_;
  };
}