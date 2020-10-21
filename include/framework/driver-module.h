#pragma once
#include "input-controller.h"

namespace godspeed
{
  namespace framework
  {
    class DriverModule
    {
      public:
        DriverModule();

        /**
        * Updates the driver module
        *
        * This is called once every time a dependent input variable
        * changes value.
        */
        virtual void update();

        /**
        * An interface for connecting input variables to slots
        *
        * A slot here is an individual input to the driver module
        * and an input variable is the input that fulfills that.
        * Slots should be well defined and be indexed by an enum
        * provided by the driver module.
        */
        virtual void connect(int slot, InputVariable &var, InputVariable::InputVariableEvent evt = InputVariable::valueChanged);

      protected:
        void addDependency(InputVariable &var, InputVariable::InputVariableEvent evt);
        void removeDependency(InputVariable &var, InputVariable::InputVariableEvent evt);
    };
  }
}