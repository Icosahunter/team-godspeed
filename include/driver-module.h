#include "input-controller.h"

namespace godspeed
{
  class DriverModule
  {
    public:
      virtual void update();
      DriverModule(InputController inputController);
      void addInputDependency(std::string input_name);
      void removeInputDependency(std::string input_name);
    
    private:
      InputController inputController_;
  };
}