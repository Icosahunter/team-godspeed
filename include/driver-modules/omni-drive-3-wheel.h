#pragma once
#include "framework/driver-module.h"
#include "vex.h"

namespace godspeed 
{
  namespace driverModules
  {
    class OmniDrive3Wheel : public framework::DriverModule
    {
      public:
        enum direction {xDirection, yDirection};
        OmniDrive3Wheel(motor &m1, motor &m2, motor &m3);
        void update();
        void connect(int slot, framework::InputVariable &var, framework::InputVariable::InputVariableEvent evt = framework::InputVariable::valueChanged);
      
      private:
        framework::InputVariable* xSpeed_;
        framework::InputVariable* ySpeed_;
        void setMotorSpeed(double motorSpeed, motor &m);
        motor* motor1_;
        motor* motor2_;
        motor* motor3_;
    };
  }
}