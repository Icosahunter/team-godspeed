#include "vex.h"
#include "event.h"

namespace godspeed
{
  class Input
  {
    public:
      virtual void* value();
      virtual void update();
      Event valueChanged = Event();
  };
}
