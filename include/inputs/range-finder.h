#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    /// \brief A namespace containing functions to access the distance values from all the rangefinders
    namespace RangeFinderSuite
    {
      /// \brief returns the distance value of Range Finder 1
      double RangeFinder() { return (double)RangeFinder1.distance(mm); }
    }
  }
}