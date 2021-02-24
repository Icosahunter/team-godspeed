#include "inputs/path-script.h"

namespace godspeed
{
  namespace inputs
  {
        double PathScript::xVar = 0;

        double PathScript::yVar = 0;

        double PathScript::angleVar = 0;

        bool PathScript::abortPath = false;

        PathScript *PathScript::currentPath = nullptr;

        std::list<COMMAND_TUPLE>::iterator PathScript::pathIndex = std::list<COMMAND_TUPLE>::iterator();
  }
}