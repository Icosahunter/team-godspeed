#include "input-controller.h"

namespace godspeed
{
  class DriverModule
  {
    public:
      virtual void update();
      void addInputDependency(Input input);
      void removeInputDependency(Input input);
  };
}