#include "framework/input-controller.h"

namespace godspeed
{
  namespace framework
  {
    void InputController::update()
    {
      for (auto &input: InputController::inputs_)
      {
        input.update();
      }
    }

    InputController InputController::operator+=(Input input)
    {
      inputs_.push_back(input);
      return *this;
    }

    InputController InputController::operator-=(Input input)
    {
      inputs_.remove(input);
      return *this;
    }
  }
}