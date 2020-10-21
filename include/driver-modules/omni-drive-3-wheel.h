#pragma once
#include "framework/data-sink-d.h"
#include "vex.h"
#include <cmath>

namespace godspeed
{
  namespace OmniDrive3Wheel
  {
    void update();
    void setMotorSpeed(double motorSpeed, motor &m);

    extern DataSinkD xDirection;
    extern DataSinkD yDirection;
  }
}