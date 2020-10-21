#include "framework/event.h"

namespace godspeed
{
  namespace framework
  {

    Event::Event()
    {
      
    }

    void Event::raise()
    {
      int c = 0;
      for(auto& x : handlers_)
      {
        if (c < handlers_.size())
        {
          (x.first)(x.second);
        }
        else
        {
          break;
        }
        c++;
      }
    }

    Event Event::addHandler(void (*handler)(void*), void* args)
    {
      handlers_.emplace(handler, args);
      return *this;
    }

    Event Event::removeHandler(void (*handler)(void*))
    {
      handlers_.erase(handler);
      return *this;
    }
  }
}