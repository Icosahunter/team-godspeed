#include "active-object.h"

namespace godspeed
{
      /**
      * The actual function handed to the thread to run
      *
      * This function loops through the overrided update() method as 
      * long as isRunning() returns true. The parameter it takes is 
      * a reference to the ActiveObject. This is defined outside the 
      * class because you cannot run a class method on the thread object.
      */
      void ActiveObject_upd(void *args)
      {
        while (static_cast<ActiveObject*>(args)->isRunning())
          static_cast<ActiveObject*>(args)->update();
      }

      void ActiveObject::start()
      {
        if (!isRunning_)
        {
          isRunning_ = true;
          thread_ = vex::thread(ActiveObject_upd, this);
        }
      }

      void ActiveObject::stop()
      {
        isRunning_ = false;
      }

      int32_t ActiveObject::threadID()
      {
        return thread_.get_id();
      }

      bool ActiveObject::isRunning()
      {
        return isRunning_;
      }

      void ActiveObject::setPriority(int32_t priority)
      {
        thread_.setPriority(priority);
      }

      int32_t ActiveObject::priority()
      {
        return thread_.priority();
      }
}