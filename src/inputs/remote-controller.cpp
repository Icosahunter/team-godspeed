#include "inputs/remote-controller.h"

namespace godspeed
{
  namespace inputs
  {
    DataSource RemoteController::RemoteController::upButton = DataSource(0,1, upBtnVal, upBtnSubscribe);;
    DataSource RemoteController::downButton = DataSource(0,1, downBtnVal, downBtnSubscribe);
    DataSource RemoteController::rightButton = DataSource(0,1, rightBtnVal, rightBtnSubscribe);
    DataSource RemoteController::leftButton = DataSource(0,1, leftBtnVal, leftBtnSubscribe);

    DataSource RemoteController::xButton = DataSource(0,1, xBtnVal, yBtnSubscribe);
    DataSource RemoteController::yButton = DataSource(0,1, yBtnVal, xBtnSubscribe);
    DataSource RemoteController::aButton = DataSource(0,1, aBtnVal, aBtnSubscribe);
    DataSource RemoteController::bButton = DataSource(0,1, bBtnVal, bBtnSubscribe);

    DataSource RemoteController::rightTrigger = DataSource(0,1, rtVal, rtSubscribe);
    DataSource RemoteController::rightBumper = DataSource(0,1, rbVal, rbSubscribe);
    DataSource RemoteController::leftTrigger = DataSource(0,1, ltVal, ltSubscribe);
    DataSource RemoteController::leftBumper = DataSource(0,1, lbVal, lbSubscribe);

    DataSource RemoteController::xLeftStick = DataSource(-100,100, xlsVal, xlsSubscribe);
    DataSource RemoteController::yLeftStick = DataSource(-100,100, ylsVal, ylsSubscribe);
    DataSource RemoteController::xRightStick = DataSource(-100,100, xrsVal, xrsSubscribe);
    DataSource RemoteController::yRightStick = DataSource(-100,100, yrsVal, yrsSubscribe);

    double RemoteController::upBtnVal() { return (double)Controller1.ButtonUp.pressing(); }
    double RemoteController::downBtnVal() { return (double)Controller1.ButtonDown.pressing(); }
    double RemoteController::rightBtnVal() { return (double)Controller1.ButtonRight.pressing(); }
    double RemoteController::leftBtnVal() { return (double)Controller1.ButtonLeft.pressing(); }
    double RemoteController::xBtnVal() { return (double)Controller1.ButtonX.pressing(); }
    double RemoteController::yBtnVal() { return (double)Controller1.ButtonY.pressing(); }
    double RemoteController::aBtnVal() { return (double)Controller1.ButtonA.pressing(); }
    double RemoteController::bBtnVal() { return (double)Controller1.ButtonB.pressing(); }
    double RemoteController::rtVal() { return (double)Controller1.ButtonR2.pressing(); }
    double RemoteController::rbVal() { return (double)Controller1.ButtonR1.pressing(); }
    double RemoteController::ltVal() { return (double)Controller1.ButtonL2.pressing(); }
    double RemoteController::lbVal() { return (double)Controller1.ButtonL1.pressing(); }
    double RemoteController::xlsVal() { return (double)Controller1.Axis4.position(); }
    double RemoteController::ylsVal() { return (double)Controller1.Axis3.position(); }
    double RemoteController::xrsVal() { return (double)Controller1.Axis1.position(); }
    double RemoteController::yrsVal() { return (double)Controller1.Axis2.position(); }

    void RemoteController::upBtnSubscribe(void (*callback)(void)) { Controller1.ButtonUp.pressed(callback); Controller1.ButtonUp.released(callback); }
    void RemoteController::downBtnSubscribe(void (*callback)(void)) { Controller1.ButtonDown.pressed(callback); Controller1.ButtonDown.released(callback); }
    void RemoteController::rightBtnSubscribe(void (*callback)(void)) { Controller1.ButtonRight.pressed(callback); Controller1.ButtonRight.released(callback); }
    void RemoteController::leftBtnSubscribe(void (*callback)(void)) { Controller1.ButtonLeft.pressed(callback); Controller1.ButtonLeft.released(callback); }
    void RemoteController::xBtnSubscribe(void (*callback)(void)) { Controller1.ButtonX.pressed(callback); Controller1.ButtonX.released(callback); }
    void RemoteController::yBtnSubscribe(void (*callback)(void)) { Controller1.ButtonY.pressed(callback); Controller1.ButtonY.released(callback); }
    void RemoteController::aBtnSubscribe(void (*callback)(void)) { Controller1.ButtonA.pressed(callback); Controller1.ButtonA.released(callback); }
    void RemoteController::bBtnSubscribe(void (*callback)(void)) { Controller1.ButtonB.pressed(callback); Controller1.ButtonB.released(callback); }
    void RemoteController::rtSubscribe(void (*callback)(void)) { Controller1.ButtonR2.pressed(callback); Controller1.ButtonR2.released(callback); }
    void RemoteController::rbSubscribe(void (*callback)(void)) { Controller1.ButtonR1.pressed(callback); Controller1.ButtonR1.released(callback); }
    void RemoteController::ltSubscribe(void (*callback)(void)) { Controller1.ButtonL2.pressed(callback); Controller1.ButtonL2.released(callback); }
    void RemoteController::lbSubscribe(void (*callback)(void)) { Controller1.ButtonL1.pressed(callback); Controller1.ButtonL1.released(callback); }
    void RemoteController::xlsSubscribe(void (*callback)(void)) { Controller1.Axis4.changed(callback); }
    void RemoteController::ylsSubscribe(void (*callback)(void)) { Controller1.Axis3.changed(callback); }
    void RemoteController::xrsSubscribe(void (*callback)(void)) { Controller1.Axis1.changed(callback); }
    void RemoteController::yrsSubscribe(void (*callback)(void)) { Controller1.Axis2.changed(callback); }
  }
}