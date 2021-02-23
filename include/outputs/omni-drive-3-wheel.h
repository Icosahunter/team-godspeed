#pragma once
#include "outputs/output-utilities.h"
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    /// \brief A namespace with functions for controlling the drive train
    namespace OmniDrive3Wheel
    {
      using namespace OutputUtilities;
      
      /// \brief A variable to track the current desired x-speed
      double XSpeedVar;

      /// \brief A variable to track the current desired y-speed
      double YSpeedVar;

      /// \brief A variable to track the current desired angular speed
      double AngleSpeedVar;

      /// \brief Set the X, Y, and angular velocities of the drivetrain
      void SetVelocity(double x, double y, double a)
      {
        XSpeedVar = x;
        YSpeedVar = y;
        AngleSpeedVar = a;

        // Describes the direction and magnitude the robot needs to turn
        double angVel = 0.333 * a;
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
        //Brain.Screen.clearScreen();
        //Brain.Screen.setCursor(1, 1);
        //Brain.Screen.print(x);
        //Brain.Screen.newLine();
        //Brain.Screen.print(y);
        //Brain.Screen.newLine();
        //Brain.Screen.print(angVel);
        //Brain.Screen.newLine();

        // Set the speed and direction of the motors so that when we turn them on, the robot moves in the desired direction (the direction the joystick is pointing)

        setMotorSpeed(m1spd, FrontRightMotor);
        setMotorSpeed(m2spd, FrontLeftMotor);
        setMotorSpeed(m3spd, BackMotor);
      }

      /// \brief Sets the x-speed of the drivetrain
      void XSpeed(double x)
      {
        SetVelocity(x, YSpeedVar, AngleSpeedVar);
      }

      /// \brief Sets the y-speed of the drivetrain
      void YSpeed(double y)
      {
        SetVelocity(XSpeedVar, y, AngleSpeedVar);
      }

      /// \brief Sets the angular speed of the drivetrain
      void AngleSpeed(double a)
      {
        SetVelocity(XSpeedVar, YSpeedVar, a);
      }
    }
  }
}