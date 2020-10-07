#include "framework/driver-module.h"

namespace godspeed
{
  namespace framework
  {
    void DriverModule_upd(void *args)
    {
      static_cast<DriverModule*>(args)->update();
    }

    void DriverModule::addInputDependency(Input input)
    {
      input.valueChanged.addHandler(DriverModule_upd, this);
    }

    void DriverModule::removeInputDependency(Input input)
    {
      input.valueChanged.removeHandler(DriverModule_upd);
    }
  }
}
