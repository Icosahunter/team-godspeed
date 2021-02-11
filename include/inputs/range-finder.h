#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    namespace rangefinders
    {
      double RangeFinder() { return (double)RangeFinder1.distance(mm); }
    }
  }
}