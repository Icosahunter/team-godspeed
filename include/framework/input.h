#include "vex.h"
#include "event.h"
#include "value-info.h"

namespace godspeed
{
  namespace framework
  {
    /**
    * An abstract class representing an input object
    *
    * The class itself should represent a type of input, 
    * though not necessarily a type of sensor. Should take 
    * a port number or other identifier in the constructor 
    * to specify the exact input.
    */
    class Input
    {
      public:
        /**
        * The value getter for the input
        *
        * Can return any value but will need to be cast and
        * dereferenced by the object using the value.
        */
        virtual void* value();

        /**
        * The function to update the value of the input
        *
        * This will be called repeatedly by the input controller
        * if it is added to one.
        */
        void update();

        /**
        * The type of the object that value() returns a pointer to
        *
        * Objects that use an input can query for it's type allowing 
        * them to provide support for multiple input value types.
        */
        virtual ValueInfo valueInfo();

        /**
        * This event is raised whenever the value of the input changes
        *
        * It should be raised by the update method whenever the new
        * value is different then it was from the last update.
        */
        Event valueChanged = Event();

        /**
        * This event is raised whenever the value of the input changes from it's typical value
        *
        * It should be raised by the update method whenever the value was
        * equal to typical and has now changed to something else
        *
        */
        Event valueDeviated = Event();
    };
  }
}
