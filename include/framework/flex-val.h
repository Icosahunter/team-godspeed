#include "vex.h"

namespace godspeed
{
  namespace framework
  {
    class FlexVal
    {
      public:
      
        void operator = (const int i);
        void operator = (const float f);
        void operator = (const double d);
        void operator = (const bool b);

      private:

        std::string value_;
    };
  }
}