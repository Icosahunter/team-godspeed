#pragma once
#include "framework/data-source.h"
#include <list>
#include <tuple>

namespace godspeed
{
  namespace inputs
  {
    using namespace framework;

    class PathScript
    {
      private:
        static double xDirVal();
        static double yDirVal();

      public:
        static DataSource xDirection;
        static DataSource yDirection;
        static std::list<std::tuple<double, double, double>> path; //list of commands of form xdir, ydir, duration
        static bool loop;
        static std::list<std::tuple<double, double, double>>::iterator pathIndex;
    };
  }
}