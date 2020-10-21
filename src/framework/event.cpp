#include "framework/event.h"

namespace godspeed
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
        (x.first)();
      }
      else
      {
        break;
      }
      c++;
    }
  }

  Event Event::addHandler(void (*handler)(void))
  {
    //handlers_.emplace(handler);
    return *this;
  }

  Event Event::removeHandler(void (*handler)(void))
  {
    //handlers_.erase(handler);
    return *this;
  }
}