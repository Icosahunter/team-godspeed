#include "framework/driver-module.h"

namespace godspeed
{
  namespace framework
  {
    void DriverModule_upd(void *args)
    {
      static_cast<DriverModule*>(args)->update();
    }

    void DriverModule::addDependency(InputVariable &var, InputVariable::InputVariableEvent evt)
    {
      switch(evt)
      {
          case InputVariable::valueChanged: var.valueChangedEvent.addHandler(DriverModule_upd, this); break;
          case InputVariable::valueDeviated: var.valueDeviatedEvent.addHandler(DriverModule_upd, this); break;
      }
    }

    void DriverModule::removeDependency(InputVariable &var, InputVariable::InputVariableEvent evt)
    {
      switch(evt)
      {
          case InputVariable::valueChanged: var.valueChangedEvent.removeHandler(DriverModule_upd); break;
          case InputVariable::valueDeviated: var.valueDeviatedEvent.removeHandler(DriverModule_upd); break;
      }
    }
  }
}
