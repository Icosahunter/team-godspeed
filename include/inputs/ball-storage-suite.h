#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    namespace BallStorage
    {
      int BallCounter = 0;
      double BallCount()
      {
        return BallCounter;
      }
    }
  }
}