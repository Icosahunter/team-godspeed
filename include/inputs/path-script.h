#pragma once
#include "framework/data-source.h"
#include "framework/data-sink-b.h"
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
        static double durVal();
        static void (*xCallback)(void);
        static void (*yCallback)(void);
        static void xSubscribe(void (*callback)(void));
        static void ySubscribe(void (*callback)(void));
        static void update();
        static bool abortPath;
        static void start();
        static void abort();

      public:
        static DataSource xDirection;
        static DataSource yDirection;
        static DataSinkB startTrigger;
        static DataSinkB abortTrigger;
        static std::list<std::tuple<double, double, double>> path; //list of commands of form xdir, ydir, duration
        static bool loop;
        static std::list<std::tuple<double, double, double>>::iterator pathIndex;
    };
  }
}