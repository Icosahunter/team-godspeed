#include "vex.h"

namespace godspeed
{
  namespace framework
  {
    class InputValue
    {
      public:
        float value;
        float max = 0;
        float typical = 0;
        float min = 0;
    };
  }
}