#include "vex.h"
#include "event.h"

namespace godspeed
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
      virtual void update();

      /**
      * This event is raised whenever the value of the input changes
      *
      * It should be raised by the update method whenever the new
      * value is different then it was from the last update.
      */
      Event valueChanged = Event();
  };
}
