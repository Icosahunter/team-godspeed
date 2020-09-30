#include "active-object.h"

namespace godspeed
{
      void ActiveObject_upd(void *args)
      {
        static_cast<ActiveObject*>(args)->update();
      }

      ActiveObject::ActiveObject() { }

      void ActiveObject::start()
      {
        isRunning_ = true;
        thread_ = vex::thread(ActiveObject_upd, this);
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