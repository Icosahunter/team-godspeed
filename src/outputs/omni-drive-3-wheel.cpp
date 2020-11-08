#include "outputs/omni-drive-3-wheel.h"

namespace godspeed 
{
  namespace outputs
  {
    DataSinkD OmniDrive3Wheel::xDirection = DataSinkD(-1, 1, update);
    DataSinkD OmniDrive3Wheel::yDirection = DataSinkD(-1, 1, update);

    void OmniDrive3Wheel::update()
    {
      // Read in the x coordinate value of
      // the left joystick on the controller
      double x = xDirection.value(); 
      // Read in the y coordinate value of
      // the left joystick on the controller
      double y = yDirection.value();
      // Calculate the angle between the x and y 
      // directional vectors to determine the 
      // direction we want the robot to move
      double ang = atan2(y, x); 
      // Calculate the magnitude that we want from the 
      // robot's movement from the x and y directional vectors
      double mag = sqrt(pow(y, 2) + pow(x, 2)); 
      // Set Front Right Wheel (motor 1) speed using wheel equation
      double m1spd = mag*(2.0/3)*cos(ang + M_PI/3); 
      // Set Front Left Wheel (motor 2) speed using wheel equation
      double m2spd = mag*(2.0/3)*cos(ang + 5*M_PI/3); 
      // Set Back Wheel (motor 3) speed using wheel equation
      double m3spd = mag*(2.0/3)*cos(ang + M_PI); 

      // Print the X and Y coordinates of the controller's left joystick on the first line of the VEX Brain's screen
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(x);
      Brain.Screen.newLine();
      Brain.Screen.print(y);
      Brain.Screen.newLine();
      task::sleep(100);
      Brain.Screen.clearScreen();

      // Set the speed and direction of the motors so that when we turn them on, the robot moves in the desired direction (the direction the joystick is pointing)
      setMotorSpeed(m1spd, Motor1);
      setMotorSpeed(m2spd, Motor2);
      setMotorSpeed(m3spd, Motor3);
    }

    void OmniDrive3Wheel::setMotorSpeed(double motorSpeed, motor &m)
    {
      if (motorSpeed < 0)
      {
        m.setReversed(false);
        if (motorSpeed < -1)
        {
          m.setVelocity(100*motorSpeed, percentUnits::pct);
        }
        else
        {
          m.setVelocity(100, percentUnits::pct);
        }
      }
      else if (motorSpeed > 0)
      {
        m.setReversed(true);
        if (motorSpeed > 1)
        {
          m.setVelocity(100*motorSpeed, percentUnits::pct);
        }
        else
        {
          m.setVelocity(100, percentUnits::pct);
        }
      }
      else
      {
        m.setVelocity(0, percentUnits::pct);
      }
    }
  }
}