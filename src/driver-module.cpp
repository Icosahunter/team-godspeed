#include "driver-module.h"

namespace godspeed
{
  void DriverModule_upd(void *args)
  {
    static_cast<DriverModule*>(args)->update();
  }

  DriverModule::DriverModule(InputController inputController)
  {
    inputController_ = inputController;
  }

  void DriverModule::addInputDependency(std::string inputName)
  {
    inputController_[inputName].valueChanged.addHandler(DriverModule_upd, this);
  }

  void DriverModule::removeInputDependency(std::string inputName)
  {
    inputController_[inputName].valueChanged.removeHandler(DriverModule_upd);
  }
}
