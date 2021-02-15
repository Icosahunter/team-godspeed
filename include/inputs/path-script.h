#pragma once
#include "vex.h"
#define COMMAND_TUPLE std::tuple<double, double, double, double>

namespace godspeed
{
  namespace inputs
  {
    /** 
    * \brief A class for creating scripted paths for the robot to take
    * 
    * The paths are scripted using "commands" which are tuples consisting of an
    * x-speed, a y-speed, an angular speed, and a duration. First create an
    * instance of PathScript, then add all commands you want, then call PathScript::ExecutePath()
    * passing in the PathScript you just created as the argument. This will immediately begin
    * execution of the path. Path execution proceeds by recursive time-delayed updates which update
    * variables, then whatever is bound the X(), Y(), and Angle() will have access to the updated variables.
    * So the udpates are asyncronous from the actual movement changes and may not be deterministic.
    */
    class PathScript
    {
      public:
        double static X() { return xVar; }
        double static Y() { return yVar; }
        double static Angle() { return angleVar; }

        /// \brief List of commands of form x-speed, y-speed, angle-speed, duration
        std::list<COMMAND_TUPLE> path;
        
        /// \brief Set this to true if you wish the path script to repeat after finishing
        bool loop;

        /// \brief Starts execution of the given path
        void static ExecutePath(PathScript &path)
        {
          abortPath = false;
          currentPath = &path;
          pathIndex = path.path.begin();
          update();
        }

        /// \brief Flags the current path to stop execution once the current update cycle is finished
        void static Abort()
        {
          abortPath = true;
        }

        /// \brief Adds a command to the path script
        void AddCommand(double x, double y, double a, double duration)
        {
          path.push_back(COMMAND_TUPLE(x, y, a, duration));
        }

      private:

        /// \brief A variable to track the current desired x-speed
        double static xVar;

        /// \brief A variable to track the current desired y-speed
        double static yVar;

        /// \brief A variable to track the current desired angular speed
        double static angleVar;

        /// \brief Flag to signal the update() to stop once the current update cycle is done
        bool static abortPath;

        /// \brief A reference to the current path being executed
        PathScript static *currentPath;

        /// \brief An iterator to keep track of the current command being executed in the path
        std::list<COMMAND_TUPLE>::iterator static pathIndex;

        /// \brief Updates the variables and recursively calls itself at the duration values
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

        /// \brief Retrieve the duration value using the current path index
        double static durVal()
        {
          return std::get<3>(*pathIndex);
        }

        /// \brief Update the velocity variables using the current path index
        void static updateVars()
        {
          xVar = std::get<0>(*pathIndex);
          yVar = std::get<1>(*pathIndex);
          angleVar = std::get<2>(*pathIndex);
        }
    };
  }
}