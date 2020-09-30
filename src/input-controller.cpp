#include "input-controller.h"

namespace godspeed
{
  void InputController::update()
  {
    for (auto &input: InputController::inputs_)
    {
      input.second.update();
    }
  }

  InputController InputController::operator+=(Input input)
  {
    inputs_.emplace(input.name(), input);
    return *this;
  }

  InputController InputController::operator-=(Input input)
  {
    inputs_.erase(input.name());
    return *this;
  }

  Input InputController::operator[](std::string inputName)
  {
    return inputs_[inputName];
  }
}