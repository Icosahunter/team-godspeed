#include "active-object.h"
#include "input.h"
#include <map>
#include <string>

namespace godspeed
{
  class InputController : ActiveObject
  {
    public:
      InputController operator+=(Input input);
      InputController operator-=(Input input);
      Input operator[](std::string inputName);

    protected:
      void update() override;
      std::map<std::string, Input> inputs_ = std::map<std::string, Input>();
  };
}