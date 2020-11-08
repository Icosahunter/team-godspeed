#pragma once
#include "framework/data-sink-d.h"
#include "vex.h"
#include <cmath>

namespace godspeed
{
  /**
  * A namespace containing data sink objects corresponding to the drivetrain
  *
  * This namespace contains data sink objects for the x velocity and y velocity
  * of the drivetrain where positive y faces toward the front of the robot and
  * positive x faces to the right.
  */
  namespace OmniDrive3Wheel
  {
    /// The function to be called when a connected data source changes value
    void update();

    /// Sets the speed of a motor
    void setMotorSpeed(double motorSpeed, motor &m);

    /**
    * The data sink for the x velocity of the drivetrain
    *
    * Positive x faces to the right of the robot.
    */
    extern DataSinkD xDirection;

    /**
    * The data sink for the y velocity of the drivetrain
    *
    * Positive y faces toward the front of the robot.
    */
    extern DataSinkD yDirection;
  }
}