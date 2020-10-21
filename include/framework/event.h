#pragma once
#include "vex.h"
#include <map>

namespace godspeed
{
  namespace framework
  {
    class Event
    {
      public:
        Event();
        void raise();
        Event addHandler(void (*handler)(void*), void* args = nullptr);
        Event removeHandler(void (*handler)(void*));
      
      private:
        std::map <void (*)(void*), void*> handlers_;
    };
  }
}