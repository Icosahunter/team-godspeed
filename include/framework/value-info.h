#include "vex.h"

namespace godspeed
{
  namespace framework
  {
    enum ValueType { int_val, bool_val, float_val, str_val, unspecified };
    class ValueInfo
    {
      public:
        ValueType type = unspecified;
        void* max = 0;
        void* typical = 0;
        void* min = 0;
    };
  }
}