#include "inputs/path-script.h"

namespace godspeed
{
  namespace PathController
  {

    namespace PcValFuncs
    {
      double xDirVal()
      {
        return std::get<0>(*pathIndex);
      }

      double yDirVal()
      {
        return std::get<1>(*pathIndex);
      }
    }

    DataSource xDirection;
    DataSource yDirection;
    std::list<std::tuple<double, double, double>> path;
    bool loop;
    std::list<std::tuple<double, double, double>>::iterator pathIndex = path.begin();
    
  }
}