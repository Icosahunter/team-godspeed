#include "input-controller.h"

namespace godspeed
{
  namespace framework
  {
    class DriverModule
    {
      public:
        DriverModule(Input input);
        virtual void update();
        void addInputDependency(Input input);
        void removeInputDependency(Input input);
    };
  }
}