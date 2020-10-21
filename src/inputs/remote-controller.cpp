#include "inputs/remote-controller.h"

namespace godspeed 
{
  namespace inputs
  {
    RemoteController::RemoteController(controller &device)
    {
      device_ = &device;
      vars_[upButton] = framework::InputVariable(0,0,1);
      vars_[downButton] = framework::InputVariable(0,0,1);
      vars_[rightButton] = framework::InputVariable(0,0,1);
      vars_[leftButton] = framework::InputVariable(0,0,1);

      vars_[xButton] = framework::InputVariable(0,0,1);
      vars_[yButton] = framework::InputVariable(0,0,1);
      vars_[aButton] = framework::InputVariable(0,0,1);
      vars_[bButton] = framework::InputVariable(0,0,1);

      vars_[rightTrigger] = framework::InputVariable(0,0,1);
      vars_[rightBumper] = framework::InputVariable(0,0,1);
      vars_[leftTrigger] = framework::InputVariable(0,0,1);
      vars_[leftBumper] = framework::InputVariable(0,0,1);

      vars_[xLeftStick] = framework::InputVariable(-1,0,1);
      vars_[yLeftStick] = framework::InputVariable(-1,0,1);
      vars_[xRightStick] = framework::InputVariable(-1,0,1);
      vars_[yRightStick] = framework::InputVariable(-1,0,1);
    }

    RemoteController::update()
    {
      for(int i = 0; i < 16; i ++)
      {
        
      }
    }
  }
}