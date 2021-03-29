#pragma once
#include "vex.h"

namespace godspeed
{
  class Debouncer
  {
    public:

    int Timeout;

    Debouncer(int timeout = 100)
    {
      Timeout = timeout;
    }

    bool Debounce()
    {
      if ((Brain.Timer.time() - t0) < Timeout)
      {
        return false;
      }
      else
      {
        t0 = Brain.Timer.time();
        return true;
      }
    }

    private:

    int t0;
  };
}