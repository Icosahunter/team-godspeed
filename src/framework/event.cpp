#include "framework/event.h"

namespace godspeed
{
  namespace framework
  {
    void Event::raise()
    {
      for(auto i : Event::handlers_)
      {
        (*i.first)(i.second);
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