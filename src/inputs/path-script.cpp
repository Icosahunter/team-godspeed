#include "inputs/path-script.h"

namespace godspeed
{
  namespace inputs
  {

    DataSource PathScript::xDirection = DataSource(-1, 1, xDirVal, xSubscribe);
    DataSource PathScript::yDirection = DataSource(-1, 1, yDirVal, ySubscribe);
    DataSinkB PathScript::startTrigger = DataSinkB(start);
    DataSinkB PathScript::abortTrigger = DataSinkB(abort);
    std::list<std::tuple<double, double, double>> PathScript::path = std::list<std::tuple<double, double, double>>();
    bool PathScript::loop = false;
    std::list<std::tuple<double, double, double>>::iterator PathScript::pathIndex = path.begin();
    void (*PathScript::xCallback)(void);
    void (*PathScript::yCallback)(void);
    bool PathScript::abortPath = false;

    double PathScript::xDirVal()
    {
      return std::get<0>(*pathIndex);
    }

    double PathScript::yDirVal()
    {
      return std::get<1>(*pathIndex);
    }

    double PathScript::durVal()
    {
      return std::get<2>(*pathIndex);
    }

    void PathScript::xSubscribe(void (*callback)(void))
    {
      xCallback = callback;
    }

    void PathScript::ySubscribe(void (*callback)(void))
    {
      yCallback = callback;
    }

    void PathScript::update()
    {
      if (!abortPath)
      {
        if (pathIndex != path.end())
        {
          xCallback();
          yCallback();
          pathIndex++;
          timer::event(update, durVal());
        }
        else
        {
          xCallback();
          yCallback();
          if (loop)
          {
            pathIndex = path.begin();
            timer::event(update, durVal());
          }
        }
      }
    }

    void PathScript::start()
    {
      if (startTrigger.value())
      {
        abortPath = false;
        pathIndex = path.begin();
        update();
      }
    }

    void PathScript::abort()
    {
      if (abortTrigger.value())
      {
        abortPath = true;
      }
    }

    void PathScript::addCommand(double x, double y, double duration)
    {
      path.push_back(std::tuple<double, double, double>(x, y, duration));
    }
  }
}