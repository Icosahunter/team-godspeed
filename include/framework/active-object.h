#include "vex.h"

namespace godspeed
{
  namespace framework
  {
    /**
    * Abstract class for an object with it's own control thread
    * 
    * Provides a framework for creating very simple active objects. 
    * Has a single thread that loops a function with no arguments or
    * returns. This thread is created on running start and killed on
    * running stop.
    */
    class ActiveObject
    {
      public:
        /**
        * Starts the active object
        *
        * Creates a new thread that loops through the update function,
        * and starts it if the object is not already running.
        */
        void start();

        /**
        * Stops the active object
        *
        * Kills the current thread the object is running on after it
        * finishes the current loop through.
        */
        void stop();

        ///Gets the ID of the current thread
        int32_t threadID();

        ///Returns true if the object is currently running
        bool isRunning();

        ///Sets the priority of the thread the object is running on
        void setPriority(int32_t priority);

        ///Gets the priority of the thread the object is running on
        int32_t priority();

        /**
        * The update function that is looped while the object is running
        *
        * Must be overrided in a derivitive class. Note that to stop the
        * thread the update function or an external object must call the
        * stop() method. The update function will loop indefinitely if no 
        * stop is called.
        */
        virtual void update();

      private:

        ///The thread that the object runs on
        vex::thread thread_;

        /**
        * The boolean used to control the thread
        *
        * This value is set to true when a thread starts and is set to
        * false by the stop() method. This signals the object to stop
        * executing when it reaches the end of it's update function.
        */
        bool isRunning_ = false;
        
    };
  }
}
