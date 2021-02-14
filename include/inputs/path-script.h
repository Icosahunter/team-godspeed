#pragma once
#include "vex.h"
#include <list>
#include <tuple>
#define COMMAND_TUPLE std::tuple<double, double, double, double>

namespace godspeed
{
  namespace inputs
  {
    class PathScript
    {
      public:
        double static X() { return xVar; }
        double static Y() { return yVar; }
        double static Angle() { return angleVar; }

        std::list<COMMAND_TUPLE> path; //list of commands of form x-speed, y-speed, angle-speed, duration
        bool loop;

        void static ExecutePath(PathScript &path)
        {
          abortPath = false;
          currentPath = &path;
          pathIndex = path.path.begin();
          update();
        }

        void static Abort()
        {
          abortPath = true;
        }

        void AddCommand(double x, double y, double a, double duration)
        {
          path.push_back(COMMAND_TUPLE(x, y, a, duration));
        }

      private:

        double static xVar;
        double static yVar;
        double static angleVar;

        bool static abortPath;
        PathScript static *currentPath;
        std::list<COMMAND_TUPLE>::iterator static pathIndex;

        static void update()
        {
          if (!abortPath)
          {
            if (pathIndex != currentPath->path.end())
            {
              updateVars();
              pathIndex++;
              timer::event(update, durVal());
            }
            else
            {
              updateVars();
              if (currentPath->loop)
              {
                pathIndex = currentPath->path.begin();
                timer::event(update, durVal());
              }
            }
          }
        }

        double static durVal()
        {
          return std::get<3>(*pathIndex);
        }

        void static updateVars()
        {
          xVar = std::get<0>(*pathIndex);
          yVar = std::get<1>(*pathIndex);
          angleVar = std::get<2>(*pathIndex);
        }
    };
  }
}