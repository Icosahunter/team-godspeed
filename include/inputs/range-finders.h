#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    /// \brief A namespace containing functions to access the distance values from all the rangefinders
    namespace RangeFinders
    {
      double leftDistVar = 0;
      double rightDistVar = 0;
      double nearThreshold = 500;

      /// \brief returns the distance value of Left Range Finder
      double LeftDistance() 
      { 
        double d = (double)LeftRangeFinder.distance(mm);
        if (d > 30)
        {
          leftDistVar = d;
          return d;
        }
        else
        {
          return leftDistVar;
        }
      }

      /// \brief returns the distance value of Right Range Finder
      double RightDistance() 
      { 
        double d = (double)RightRangeFinder.distance(mm);
        if (d > 30)
        {
          rightDistVar = d;
          return d;
        }
        else
        {
          return rightDistVar;
        }
      }

      /// \brief returns a value between -1 and 1 representing how close an obstacle is to the right or left side of the robot respectively
      double Nearness() 
      { 
        double ld = LeftDistance();
        ld = ld < nearThreshold ? ld : nearThreshold;
        double rd = RightDistance();
        rd = rd < nearThreshold ? rd : nearThreshold;
        return (1 - ld/nearThreshold) - (1 - rd/nearThreshold);
      }
    }
  }
}