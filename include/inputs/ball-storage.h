#pragma once
#include "vex.h"
#include "framework/debouncer.h"

namespace godspeed
{
  namespace inputs
  {
    /**
    * \brief A namespace with a function for accessing the current number of balls stored in the robot
    *
    * The Init() function must be called before the ball storage tracking can begin.
    * That function attaches the inc and dec function as callbacks for when bumper A and bumper B
    * are pressed (respectively).
    */
    namespace BallStorage
    {
      Debouncer inc_debounce(1000);
      Debouncer dec_debounce(1000);

      /// \brief A variable for tracking the ball count
      int BallCounter;

      /// \brief Increment the ball count. This does NOT need to be called manually
      void inc()
      {
        if (inc_debounce.Debounce())
        {
          BallCounter++;
        }
      }

      /// \brief Decrement the ball count. This does NOT need to be called manually
      void dec()
      {
        if (dec_debounce.Debounce())
        {
          BallCounter--;
        }
      }

      /// \brief Returns the current ball count
      double BallCount()
      {
        return BallCounter;
      }

      /// \brief Setup the ball storage counter to track balls
      void Init()
      {
        BumperA.pressed(inc);
        BumperB.pressed(dec);
      }
    }
  }
}