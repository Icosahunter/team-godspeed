#include "vex.h"

namespace godspeed
{

  class ActiveObject
  {
    public:
      ActiveObject();
      void start();
      void stop();
      int32_t threadID();
      bool isRunning();
      void setPriority(int32_t priority);
      int32_t priority();
      virtual void update();

    private:
      vex::thread thread_;
      bool isRunning_ = false;
      
  };
}
