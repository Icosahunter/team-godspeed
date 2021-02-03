#pragma once
#include "framework/data-sink-d.h"
#include "outputs/output-utilities.h"
#include "vex.h"
#include <cmath>

namespace godspeed
{
  namespace outputs
  {
    using namespace framework;
    using namespace outputUtilities;
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
        * \brief The data sink for the angular velocity of the drivetrain
        *
        * Positive values indicate Clockwise rotation of the robot
        */
        static DataSinkD angularVelocity;

        /**
        * \brief The data sink for the x velocity of the drivetrain
        *
        * Positive x faces to the right of the robot.
        */
        static DataSinkD xVelocity;

        /**
        * \brief The data sink for the y velocity of the drivetrain
        *
        * Positive y faces toward the front of the robot.
        */
        static DataSinkD yVelocity;

      //private:
        /// The function to be called when a connected data source changes value
        static void update();

    };// end OmniDrive3Wheel
  }// end namespace outputs
}// end namespace godspeed