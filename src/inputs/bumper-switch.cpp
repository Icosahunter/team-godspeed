#include "inputs/bumper-switch.h"

namespace godspeed 
{
  namespace inputs
  {
    BumperSwitch::BumperSwitch(bumper &device)
    {
      device_ = &device;
    }

    void BumperSwitch::update()
    {
      int32_t v0 = pressing_;
      int32_t v1 = device_->pressing();
      if (v0 != v1)
      {
        std::time_t t1 = std::time(nullptr);
        if (static_cast<long int>(t1 - t0_) >= timeout_)
        {
          pressing_ = v1;
          if (v0 == var_.typicalValue())
          {
            var_.valueDeviatedEvent.raise();
          }
          var_.valueChangedEvent.raise();
          t0_ = t1;
        }
      }
    }

    framework::InputVariable* BumperSwitch::variables(int varId)
    {
      if (varId == switchState)
      {
        return &var_;
      }
      else
      {
        Brain.Screen.print("Error: Attempted to access invalid input slot.");
        return &var_;
      }
    }

    void BumperSwitch::setTimeout(int t)
    {
      timeout_ = t;
    }

    int BumperSwitch::timeout()
    {
      return timeout_;
    }
  }
}