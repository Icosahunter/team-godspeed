#pragma once
#include "vex.h"

namespace godspeed
{
  class LagValue
  {
    public:

      int LagTime;

      LagValue(int lagTime = 100)
      {
        LagTime = lagTime;
      }

      double Value()
      {
        if (timing && (Brain.Timer.time() - t0) < LagTime)
        {
          return oldVal;
        }
        else
        {
          timing = false;
          return newVal;
        }
      }

      void SetValue(double val)
      {
        oldVal = newVal;
        newVal = val;
        t0 = Brain.Timer.time();
        timing = true;
      }

    private:

    bool timing = false;
    int t0;
    double oldVal;
    double newVal;
  };
}