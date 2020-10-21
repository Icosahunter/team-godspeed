#pragma once
#include "vex.h"
#include "event.h"

namespace godspeed
{
  namespace framework
  {
    
    /**
    * An class representing a slot of an input device
    *
    * A particular input device may produce more than
    * one piece of data, each piece of data will be a slot.
    * The data will need to be represented as a float.
    */
    class InputVariable
    {
      public:

        enum InputVariableEvent { valueChanged, valueDeviated };

        InputVariable();

        InputVariable(double min, double typical, double max);

        /**
        * The value getter for the slot
        */
        double value();

        /**
        * The typical value of the slot
        */
        double typicalValue();

        /**
        * The maximum value the slot will have
        */
        double maxValue();

        /**
        * The minimum value the slot will have
        */
        double minValue();

        /**
        * This event is raised whenever the value of the slot changes
        *
        * It should be raised by the update method whenever the new
        * value is different then it was from the last update.
        */
        Event valueChangedEvent = Event();

        /**
        * This event is raised whenever the value of the slot changes from it's typical value
        *
        * It should be raised by the update method whenever the value was
        * equal to typical and has now changed to something else
        *
        */
        Event valueDeviatedEvent = Event();

        double value_ = 0;

        static double rescale(double desiredMin, double desiredMax, InputVariable &var);
        static bool toBool(InputVariable &var);

      private:

        double max_ = 0;
        double typical_ = 0;
        double min_ = 0;
        friend class InputDevice;
    };
  }
}