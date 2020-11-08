#include "inputs/remote-controller.h"

namespace godspeed
{
  namespace RemoteController
  {
    /// Contains the functions that return the values of the various controller inputs
    namespace RcValFuncs
    {
      double upBtnVal() { return (double)Controller1.ButtonUp.pressing(); }
      double downBtnVal() { return (double)Controller1.ButtonDown.pressing(); }
      double rightBtnVal() { return (double)Controller1.ButtonRight.pressing(); }
      double leftBtnVal() { return (double)Controller1.ButtonLeft.pressing(); }
      double xBtnVal() { return (double)Controller1.ButtonX.pressing(); }
      double yBtnVal() { return (double)Controller1.ButtonY.pressing(); }
      double aBtnVal() { return (double)Controller1.ButtonA.pressing(); }
      double bBtnVal() { return (double)Controller1.ButtonB.pressing(); }
      double rtVal() { return (double)Controller1.ButtonR2.pressing(); }
      double rbVal() { return (double)Controller1.ButtonR1.pressing(); }
      double ltVal() { return (double)Controller1.ButtonL2.pressing(); }
      double lbVal() { return (double)Controller1.ButtonL1.pressing(); }
      double xlsVal() { return (double)Controller1.Axis4.position(); }
      double ylsVal() { return (double)Controller1.Axis3.position(); }
      double xrsVal() { return (double)Controller1.Axis1.position(); }
      double yrsVal() { return (double)Controller1.Axis2.position(); }
    }

    /// Contains the functions that subscribe a function to value changes of the various controller inputs
    namespace RcSubscribeFuncs
    {
      void upBtnSubscribe(void (*callback)(void)) { Controller1.ButtonUp.pressed(callback); Controller1.ButtonUp.released(callback); }
      void downBtnSubscribe(void (*callback)(void)) { Controller1.ButtonDown.pressed(callback); Controller1.ButtonDown.released(callback); }
      void rightBtnSubscribe(void (*callback)(void)) { Controller1.ButtonRight.pressed(callback); Controller1.ButtonRight.released(callback); }
      void leftBtnSubscribe(void (*callback)(void)) { Controller1.ButtonLeft.pressed(callback); Controller1.ButtonLeft.released(callback); }
      void xBtnSubscribe(void (*callback)(void)) { Controller1.ButtonX.pressed(callback); Controller1.ButtonX.released(callback); }
      void yBtnSubscribe(void (*callback)(void)) { Controller1.ButtonY.pressed(callback); Controller1.ButtonY.released(callback); }
      void aBtnSubscribe(void (*callback)(void)) { Controller1.ButtonA.pressed(callback); Controller1.ButtonA.released(callback); }
      void bBtnSubscribe(void (*callback)(void)) { Controller1.ButtonB.pressed(callback); Controller1.ButtonB.released(callback); }
      void rtSubscribe(void (*callback)(void)) { Controller1.ButtonR2.pressed(callback); Controller1.ButtonR2.released(callback); }
      void rbSubscribe(void (*callback)(void)) { Controller1.ButtonR1.pressed(callback); Controller1.ButtonR1.released(callback); }
      void ltSubscribe(void (*callback)(void)) { Controller1.ButtonL2.pressed(callback); Controller1.ButtonL2.released(callback); }
      void lbSubscribe(void (*callback)(void)) { Controller1.ButtonL1.pressed(callback); Controller1.ButtonL1.released(callback); }
      void xlsSubscribe(void (*callback)(void)) { Controller1.Axis4.changed(callback); }
      void ylsSubscribe(void (*callback)(void)) { Controller1.Axis3.changed(callback); }
      void xrsSubscribe(void (*callback)(void)) { Controller1.Axis1.changed(callback); }
      void yrsSubscribe(void (*callback)(void)) { Controller1.Axis2.changed(callback); }
    }

    DataSource upButton = DataSource(0,1, RcValFuncs::upBtnVal, RcSubscribeFuncs::upBtnSubscribe);
    DataSource downButton = DataSource(0,1, RcValFuncs::downBtnVal, RcSubscribeFuncs::downBtnSubscribe);
    DataSource rightButton = DataSource(0,1, RcValFuncs::rightBtnVal, RcSubscribeFuncs::rightBtnSubscribe);
    DataSource leftButton = DataSource(0,1, RcValFuncs::leftBtnVal, RcSubscribeFuncs::leftBtnSubscribe);

    DataSource xButton = DataSource(0,1, RcValFuncs::xBtnVal, RcSubscribeFuncs::yBtnSubscribe);
    DataSource yButton = DataSource(0,1, RcValFuncs::yBtnVal, RcSubscribeFuncs::xBtnSubscribe);
    DataSource aButton = DataSource(0,1, RcValFuncs::aBtnVal, RcSubscribeFuncs::aBtnSubscribe);
    DataSource bButton = DataSource(0,1, RcValFuncs::bBtnVal, RcSubscribeFuncs::bBtnSubscribe);

    DataSource rightTrigger = DataSource(0,1, RcValFuncs::rtVal, RcSubscribeFuncs::rtSubscribe);
    DataSource rightBumper = DataSource(0,1, RcValFuncs::rbVal, RcSubscribeFuncs::rbSubscribe);
    DataSource leftTrigger = DataSource(0,1, RcValFuncs::ltVal, RcSubscribeFuncs::ltSubscribe);
    DataSource leftBumper = DataSource(0,1, RcValFuncs::lbVal, RcSubscribeFuncs::lbSubscribe);

    DataSource xLeftStick = DataSource(-100,100, RcValFuncs::xlsVal, RcSubscribeFuncs::xlsSubscribe);
    DataSource yLeftStick = DataSource(-100,100, RcValFuncs::ylsVal, RcSubscribeFuncs::ylsSubscribe);
    DataSource xRightStick = DataSource(-100,100, RcValFuncs::xrsVal, RcSubscribeFuncs::xrsSubscribe);
    DataSource yRightStick = DataSource(-100,100, RcValFuncs::yrsVal, RcSubscribeFuncs::yrsSubscribe);
  }
}