#include "vex.h"

namespace godspeed
{
    class TimedToggle
  {
    public:

      bool DefaultValue = false;
      int Timeout = 1000;

      TimedToggle(int timeout = 1000, bool defaultVal = false )
      {
        DefaultValue = defaultVal;
        Timeout = timeout;
        value = DefaultValue;
        timing = false;
      }

      bool Value()
      {
        return value;
      }

      void SetValue(bool val)
      {
        if (!timing)
        {
          if (val != DefaultValue)
          {
            t0 = Brain.Timer.time();
            thread t(Reset, this);
            t.detach();
          }
          value = val;
        }
      }

    private:

      bool value;
      bool timing;
      int t0;

      static void Reset(void* arg)
      {
        TimedToggle* obj = ((TimedToggle*)arg);
        obj->timing = true;
        bool done = false;
        
        while(!done)
        {
          if (Brain.Timer.time() - obj->t0 >= obj->Timeout)
          {
            obj->value = obj->DefaultValue;
            done = true;
          }
        }
        obj->timing = false;
      }
  };
}