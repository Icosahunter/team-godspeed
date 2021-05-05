#pragma once
#include "vex.h"
#include <algorithm>
#include <numeric>
#include <list>

namespace godspeed
{
  /// \brief A class to apply windowed averaging
  class WinAvg
  {
    public:

      /// \brief Size of the averaging window
      int WindowSize() { return values.size(); };

      /// \brief Returns average of current window
      double Value()
      {
        return std::accumulate(values.begin(), values.end(), 0.0)/values.size();
      }

      /// \brief Set value of all points in window
      void Initialize(double val)
      {
        for(auto &x : values)
        {
          x = val;
        }
      }

      /// \brief Add new data point to window
      void SetValue(double val)
      {
        values.pop_back();
        values.push_front(val);
      }

      /// \brief Constructor
      WinAvg(int winsize = 100)
      {
        values.resize(winsize);
      }

    private:
      std::list<double> values;
  };

  /// \brief A class to apply windowed minimum
  class WinMin
  {
    public:

      /// \brief Size of the window
      int WindowSize() { return values.size(); };

      /// \brief Returns minimum of current window
      double Value()
      {
        return *std::min_element(values.begin(), values.end());
      }

      /// \brief Set value of all points in window
      void Initialize(double val)
      {
        for(auto &x : values)
        {
          x = val;
        }
      }

      /// \brief Add new data point to window
      void SetValue(double val)
      {
        values.pop_back();
        values.push_front(val);
      }

      /// \brief Constructor
      WinMin(int winsize = 100)
      {
        values.resize(winsize);
      }

    private:
      std::list<double> values;
  };
}