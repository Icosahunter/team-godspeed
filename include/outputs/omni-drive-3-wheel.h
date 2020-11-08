#pragma once
#include "framework/data-sink-d.h"
#include "vex.h"
#include <cmath>

namespace godspeed
{
  namespace outputs
  {
    using namespace framework;
    /**
    * \brief A class containing data sink objects corresponding to the drivetrain
    *
    * This class contains data sink objects for the x velocity and y velocity
    * of the drivetrain where positive y faces toward the front of the robot and
    * positive x faces to the right.
    */
    class OmniDrive3Wheel
    {
      public:
        /**
        * The data sink for the x velocity of the drivetrain
        *
        * Positive x faces to the right of the robot.
        */
        static DataSinkD xDirection;

        /**
        * The data sink for the y velocity of the drivetrain
        *
        * Positive y faces toward the front of the robot.
        */
        static DataSinkD yDirection;

      private:
        /// The function to be called when a connected data source changes value
        static void update();

        /// Sets the speed of a motor
        static void setMotorSpeed(double motorSpeed, motor &m);
    };
  }
}