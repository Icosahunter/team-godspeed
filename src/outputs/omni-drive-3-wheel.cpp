#include "outputs/omni-drive-3-wheel.h"

namespace godspeed 
{
  namespace outputs
  {
    DataSinkD OmniDrive3Wheel::angularVelocity = DataSinkD(-1, 1, update);
    DataSinkD OmniDrive3Wheel::xVelocity = DataSinkD(-1, 1, update);
    DataSinkD OmniDrive3Wheel::yVelocity = DataSinkD(-1, 1, update);

    void OmniDrive3Wheel::update()
    {
      // Describes the direction and magnitude the robot needs to turn
      double angVel = 0.333 * angularVelocity.value();
      // Describes the velocity of the robot in the x direction (+x is to the right)
      double x = xVelocity.value(); 
      // Describes the velocity of the robot in the y direction (+y is to the front)
      double y = yVelocity.value();
      // Calculate the angle between the x and y directional vectors to determine the direction the robot is to move
      double ang = atan2(y, x);
      // Calculate the magnitude that the robot movement needs to be from the x and y directional vectors
      double mag = sqrt(pow(y, 2) + pow(x, 2)); 
      // Set Front Right Wheel (motor 1) speed using wheel equation
      double m1spd = mag*(2.0/3)*cos(ang + M_PI/3) + angVel; 
      // Set Front Left Wheel (motor 2) speed using wheel equation
      double m2spd = mag*(2.0/3)*cos(ang + 5*M_PI/3) + angVel; 
      // Set Back Wheel (motor 3) speed using wheel equation
      double m3spd = mag*(2.0/3)*cos(ang + M_PI) + angVel; 

      // Print the X and Y coordinates of the controller's left joystick on the first line of the VEX Brain's screen
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(x);
      Brain.Screen.newLine();
      Brain.Screen.print(y);
      Brain.Screen.newLine();
      Brain.Screen.print(angVel);
      Brain.Screen.newLine();
      task::sleep(100);
      Brain.Screen.clearScreen();

      // Set the speed and direction of the motors so that when we turn them on, the robot moves in the desired direction (the direction the joystick is pointing)

      setMotorSpeed(m1spd, FrontRightMotor);
      setMotorSpeed(m2spd, FrontLeftMotor);
      setMotorSpeed(m3spd, BackMotor);
    }

  }// end namespace Outputs
} // end namespace godspeed