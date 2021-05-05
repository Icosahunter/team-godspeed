#pragma once
#include "vex.h"

namespace godspeed
{
  /// \brief A class for debouncing boolean data using a delay
  class Debouncer
  {
    public:

    /// \brief Delay used for debouncing
    int Timeout;

    /// \brief Constructor
    Debouncer(int timeout = 100)
    {
      Timeout = timeout;
    }

    /// \brief Call whenever the signal switches on, and used the returned value as the actual debounced value
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