#pragma once
#include "framework/data-source.h"

namespace godspeed
{
  /**
  * A namespace containing data source objects corresponding to controller inputs
  *
  * This namespace contains 16 data source objects. Each one corresponds to an
  * individual input on the remote controller, such as the A-button or the 
  * the left stick X axis.
  */
  namespace RemoteController
  {
    /// A data source corresponding to the state of the up button
    extern DataSource upButton;

    /// A data source corresponding to the state of the down button
    extern DataSource downButton;

    /// A data source corresponding to the state of the right button
    extern DataSource rightButton;

    /// A data source corresponding to the state of the left button
    extern DataSource leftButton;


    /// A data source corresponding to the state of the X button
    extern DataSource xButton;
    /// A data source corresponding to the state of the Y button
    extern DataSource yButton;
    /// A data source corresponding to the state of the A button
    extern DataSource aButton;
    /// A data source corresponding to the state of the B button
    extern DataSource bButton;

    /// A data source corresponding to the state of the right trigger (R1)
    extern DataSource rightTrigger;
    /// A data source corresponding to the state of the right bumper (R2)
    extern DataSource rightBumper;
    /// A data source corresponding to the state of the left trigger (L1)
    extern DataSource leftTrigger;
    /// A data source corresponding to the state of the left bumper (L2)
    extern DataSource leftBumper;

    /// A data source corresponding to the state of the left joy stick's X axis
    extern DataSource xLeftStick;
    /// A data source corresponding to the state of the left joy stick's Y axis
    extern DataSource yLeftStick;
    /// A data source corresponding to the state of the right joy stick's X axis
    extern DataSource xRightStick;
    /// A data source corresponding to the state of the right joy stick's Y axis
    extern DataSource yRightStick;
  }
}