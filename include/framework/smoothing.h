#pragma once
#include "vex.h"
#include <algorithm>
#include <numeric>
#include <list>

namespace godspeed
{
  class WinAvg
  {
    public:

      double Value()
      {
        return std::accumulate(values.begin(), values.end(), 0.0)/values.size();
      }

      void Initialize(double val)
      {
        for(auto &x : values)
        {
          x = val;
        }
      }

      void SetValue(double val)
      {
        values.pop_back();
        values.push_front(val);
      }

      WinAvg(int winsize = 100)
      {
        values.resize(winsize);
      }

    private:
      std::list<double> values;
  };

  class WinMin
  {
    public:

      double Value()
      {
        return *std::min_element(values.begin(), values.end());
      }

      void Initialize(double val)
      {
        for(auto &x : values)
        {
          x = val;
        }
      }

      void SetValue(double val)
      {
        values.pop_back();
        values.push_front(val);
      }

      WinMin(int winsize = 100)
      {
        values.resize(winsize);
      }

    private:
      std::list<double> values;
  };
}