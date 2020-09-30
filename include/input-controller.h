#include "active-object.h"
#include "input.h"
#include <map>
#include <list>

namespace godspeed
{
  class InputController : ActiveObject
  {
    public:
      InputController operator+=(Input input);
      InputController operator-=(Input input);

    protected:
      void update() override;
      std::list<Input> inputs_ = std::list<Input>();
  };
}