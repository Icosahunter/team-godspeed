#pragma once
#include "vex.h"
#include <list>

namespace godspeed
{
  namespace framework
  {
    /**
    * \brief A class for implementing observer patterns
    *
    * The event class allows other objects to be notified
    * when something happens. They do this by "subscribing"
    * to the event by passing in a function that they wish
    * to have called whenever that event happens. The event
    * class will then go through it's list of functions and
    * call each one of them whenever it is raised.
    *
    * It is the job of the object creating the event to raise 
    * the event when appropriate. Other objects that wish to 
    * subscribe to the event must necessarily have access to 
    * the event object or to a public function that can receive 
    * an event handler function.
    */
    class Event
    {
      public:
        /// \brief The constructor for the event class
        Event();

        /**
        * \brief Calling this method signifies that the event happened
        *
        * When called this method will call every event handler
        * that has been added to the event.
        */
        void raise();

        /**
        * \brief Add an event handler to the event
        *
        * @param handler A function with no arguments or returns that will be called when the event happens
        */
        Event addHandler(void (*handler)(void));

        /**
        * \brief Remove a handler from the event
        *
        * To remove a handler you must have a reference to the original 
        * handler. Consequently this is usually only done by whatever 
        * object originally added the handler.
        *
        * @param handler The handler function to remove
        */
        Event removeHandler(void (*handler)(void));
      
      private:
        /// \brief The list of event handlers that have been added to the event
        std::list <void (*)(void)> handlers_;
    };
  }
}