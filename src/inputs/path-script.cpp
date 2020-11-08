#include "inputs/path-script.h"

namespace godspeed
{
  namespace inputs
  {

    double PathScript::xDirVal()
    {
      return std::get<0>(*pathIndex);
    }

    double PathScript::yDirVal()
    {
      return std::get<1>(*pathIndex);
    }

    DataSource PathScript::xDirection;
    DataSource PathScript::yDirection;
    std::list<std::tuple<double, double, double>> PathScript::path;
    bool PathScript::loop;
    std::list<std::tuple<double, double, double>>::iterator PathScript::pathIndex = path.begin();
    
  }
}