#include "inputs/bumper-switch.h"

namespace godspeed 
{
  namespace inputs
  {
    BumperSwitch::BumperSwitch(bumper* device)
    {
      device_ = device;
      vtype_.type = framework::ValueType::bool_val;
      vtype_.min = &min_;
      vtype_.typical = &typ_;
      vtype_.max = &max_;
    }

    void* BumperSwitch::value()
    {
      return &pressing_;
    }

    void BumperSwitch::update()
    {
      int32_t v0 = pressing_;
      int32_t v1 = device_->pressing();
      if (v0 != v1)
      {
        std::time_t t1 = std::time_t(nullptr);
        if (static_cast<long int>(t1 - t0_) >= timeout_)
        {
          pressing_ = v1;
          if (v0 == typ_)
          {
            valueDeviated.raise();
          }
          valueChanged.raise();
          t0_ = t1;
        }
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

    framework::ValueInfo BumperSwitch::valueType()
    {
      return vtype_;
    }
  }
}