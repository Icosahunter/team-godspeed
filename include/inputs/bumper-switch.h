#include "framework/input.h"
#include "vex.h"

namespace godspeed 
{
  namespace inputs
  {
    class BumperSwitch : framework::Input
    {
      public: 
        BumperSwitch(bumper* _device);
        void* value();
        void update();
        framework::ValueInfo valueType();
        void setTimeout(int t);
        int timeout();

      private:
        bumper* device_;
        int pressing_;
        int timeout_ = 1;
        std::time_t t0_;
        framework::ValueInfo vtype_ = framework::ValueInfo();
        bool typ_ = 0;
        bool min_ = 0;
        bool max_ = 0;
    };
  }
}