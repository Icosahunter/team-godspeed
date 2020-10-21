#pragma once
#include "framework/input-device.h"
#include "vex.h"

namespace godspeed 
{
  namespace inputs
  {
    enum BumperSwitchVars {switchState};

    class BumperSwitch : public framework::InputDevice
    {
      public: 
        BumperSwitch(bumper &_device);
        void update();
        void setTimeout(int t);
        int timeout();
        framework::InputVariable* variables(int varId);

      private:
        bumper* device_;
        int pressing_ = 0;
        int timeout_ = 1;
        std::time_t t0_ = 0;
        framework::InputVariable var_ = framework::InputVariable(0, 0, 1);
    };
  }
}