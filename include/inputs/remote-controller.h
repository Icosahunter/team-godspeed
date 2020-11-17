#pragma once
#include "framework/data-source.h"

namespace godspeed
{
  namespace inputs
  {
    using namespace framework;

    /**
    * \brief A class containing data source objects corresponding to controller inputs
    *
    * This class contains 16 data source objects. Each one corresponds to an
    * individual input on the remote controller, such as the A-button or the 
    * the left stick X axis.
    */
    class RemoteController
    {
      public:
        /// \brief A data source corresponding to the state of the up button
        static DataSource upButton;
        /// \brief A data source corresponding to the state of the down button
        static DataSource downButton;
        /// \brief A data source corresponding to the state of the right button
        static DataSource rightButton;
        /// \brief A data source corresponding to the state of the left button
        static DataSource leftButton;


        /// \brief A data source corresponding to the state of the X button
        static DataSource xButton;
        /// \brief A data source corresponding to the state of the Y button
        static DataSource yButton;
        /// \brief A data source corresponding to the state of the A button
        static DataSource aButton;
        /// \brief A data source corresponding to the state of the B button
        static DataSource bButton;

        /// \brief A data source corresponding to the state of the right trigger (R1)
        static DataSource rightTrigger;
        /// \brief A data source corresponding to the state of the right bumper (R2)
        static DataSource rightBumper;
        /// \brief A data source corresponding to the state of the left trigger (L1)
        static DataSource leftTrigger;
        /// \brief A data source corresponding to the state of the left bumper (L2)
        static DataSource leftBumper;

        /// \brief A data source corresponding to the state of the left joy stick's X axis
        static DataSource xLeftStick;
        /// \brief A data source corresponding to the state of the left joy stick's Y axis
        static DataSource yLeftStick;
        /// \brief A data source corresponding to the state of the right joy stick's X axis
        static DataSource xRightStick;
        /// \brief A data source corresponding to the state of the right joy stick's Y axis
        static DataSource yRightStick;

      private:
        static double upBtnVal();
        static double downBtnVal();
        static double rightBtnVal();
        static double leftBtnVal();
        static double xBtnVal();
        static double yBtnVal();
        static double aBtnVal();
        static double bBtnVal();
        static double rtVal();
        static double rbVal();
        static double ltVal();
        static double lbVal();
        static double xlsVal();
        static double ylsVal();
        static double xrsVal();
        static double yrsVal();

        static void upBtnSubscribe(void (*callback)(void));
        static void downBtnSubscribe(void (*callback)(void));
        static void rightBtnSubscribe(void (*callback)(void));
        static void leftBtnSubscribe(void (*callback)(void));
        static void xBtnSubscribe(void (*callback)(void));
        static void yBtnSubscribe(void (*callback)(void));
        static void aBtnSubscribe(void (*callback)(void));
        static void bBtnSubscribe(void (*callback)(void));
        static void rtSubscribe(void (*callback)(void));
        static void rbSubscribe(void (*callback)(void));
        static void ltSubscribe(void (*callback)(void));
        static void lbSubscribe(void (*callback)(void));
        static void xlsSubscribe(void (*callback)(void));
        static void ylsSubscribe(void (*callback)(void));
        static void xrsSubscribe(void (*callback)(void));
        static void yrsSubscribe(void (*callback)(void));
    };
  }
}