#include "vex.h"
#include "event.h"

namespace godspeed
{
  class Input
  {
    public:
      Input(std::string name);
      virtual void* value();
      virtual void update();
      std::string name();
      Event valueChanged = Event();

    protected:
      std::string name_;
      
  };
}
