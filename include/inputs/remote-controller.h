#pragma once
#include "framework/input-device.h"
#include "vex.h"

namespace godspeed 
{
  namespace inputs
  {
    enum RemoteControllerVars {upButton, downButton, leftButton, rightButton,
                               xButton, yButton, aButton, bButton,
                               xLeftStick, yLeftStick,
                               xRightStick, yRightStick,
                               rightTrigger, rightBumper,
                               leftTrigger, leftBumper};

    class RemoteController : public framework::InputDevice
    {
      public: 
        RemoteController(controller &_device);
        void update();
        void setTimeout(int t);
        int timeout();
        framework::InputVariable* variables(int varId);

      private:
        controller* device_;
        float varLastVals_[16];
        framework::InputVariable vars_[16];
    };
  }
}