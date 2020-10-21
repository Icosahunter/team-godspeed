#pragma once
#include "active-object.h"
#include "input-device.h"
#include <map>
#include <list>

namespace godspeed
{
  namespace framework
  {
    class InputController
    {
      public:

        static void initialize();
        static void addInputDevice(InputDevice &input);
        static void removeInputDevice(InputDevice &input);

        /**
        * Starts the active object
        *
        * Creates a new thread that loops through the update function,
        * and starts it if the object is not already running.
        */
        static void start();

        /**
        * Stops the active object
        *
        * Kills the current thread the object is running on after it
        * finishes the current loop through.
        */
        static void stop();

        ///Gets the ID of the current thread
        static int32_t threadID();

        ///Returns true if the object is currently running
        static bool isRunning();

        ///Sets the priority of the thread the object is running on
        static void setPriority(int32_t priority);

        ///Gets the priority of the thread the object is running on
        static int32_t priority();

        /**
        * The update function that is looped while the object is running
        *
        * Must be overrided in a derivitive class. Note that to stop the
        * thread the update function or an external object must call the
        * stop() method. The update function will loop indefinitely if no 
        * stop is called.
        */
        static void update();


      private:
        static std::list<InputDevice*> inputs_;
                ///The thread that the object runs on
        static vex::thread thread_;

        /**
        * The boolean used to control the thread
        *
        * This value is set to true when a thread starts and is set to
        * false by the stop() method. This signals the object to stop
        * executing when it reaches the end of it's update function.
        */
        static bool isRunning_;
        
    };
  }
}