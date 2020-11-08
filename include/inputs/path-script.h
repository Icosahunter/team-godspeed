#pragma once
#include "framework/data-source.h"
#include <list>
#include <tuple>

namespace godspeed
{
  namespace PathController
  {
    extern DataSource xDirection;
    extern DataSource yDirection;
    extern std::list<std::tuple<double, double, double>> path; //list of commands of form xdir, ydir, duration
    extern bool loop;
    extern std::list<std::tuple<double, double, double>>::iterator pathIndex;
    
  }
}