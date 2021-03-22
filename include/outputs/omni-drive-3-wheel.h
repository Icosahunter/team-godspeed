#pragma once
#include "outputs/output-utilities.h"
#include "framework/smoothing.h"
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    /// \brief A namespace with functions for controlling the drive train
    namespace OmniDrive3Wheel
    {
      using namespace OutputUtilities;
      
      /// \brief An object to track the current desired x-speed and apply smoothing to prevent jerky movement
      Smoothing XSpeedVar;

      /// \brief An object to track the current desired y-speed and apply smoothing to prevent jerky movement
      Smoothing YSpeedVar;

      /// \brief A variable to track the current desired angular speed
      double AngleSpeedVar;

      void PrintToScreen(){
        // Print the X and Y coordinates of the controller's left joystick on the first line of the VEX Brain's screen
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print(XSpeedVar);
        Controller1.Screen.newLine();
        Controller1.Screen.print(YSpeedVar);
        Controller1.Screen.newLine();
        Controller1.Screen.print(AngleSpeedVar);
        Controller1.Screen.newLine();

      }
      /// \brief Set the X, Y, and angular velocities of the drivetrain
      void SetVelocity(double x, double y, double a)
      {
        XSpeedVar.SetValue(x);
        YSpeedVar.SetValue(y);
        AngleSpeedVar = a;

        // Describes the direction and magnitude the robot needs to turn
        double angVel = 0.333 * AngleSpeedVar;
        // Calculate the angle between the x and y directional vectors to determine the direction the robot is to move
        double ang = atan2(YSpeedVar.Value(), XSpeedVar.Value());
        // Calculate the magnitude that the robot movement needs to be from the x and y directional vectors
        double mag = sqrt(pow(YSpeedVar.Value(), 2) + pow(XSpeedVar.Value(), 2));
        // Set Front Right Wheel (motor 1) speed using wheel equation
        double m1spd = mag*0.666*cos(ang + M_PI/3) + angVel; 
        // Set Front Left Wheel (motor 2) speed using wheel equation
        double m2spd = mag*0.666*cos(ang + 5*M_PI/3) + angVel; 
        // Set Back Wheel (motor 3) speed using wheel equation
        double m3spd = mag*0.666*cos(ang + M_PI) + angVel; 

        // Print the X and Y coordinates of the controller's left joystick on the first line of the VEX Brain's screen
        //Controller1.Screen.clearScreen();
        //Controller1.Screen.setCursor(1, 1);
        //Controller1.Screen.print(x);
        //Controller1.Screen.newLine();
        //Controller1.Screen.print(y);
        //Controller1.Screen.newLine();
        //Controller1.Screen.print(angVel);
        //Controller1.Screen.newLine();
        //Brain.Screen.clearScreen();
        //Brain.Screen.setCursor(1, 1);
        //Brain.Screen.print(x);
        //Brain.Screen.newLine();
        //Brain.Screen.print(y);
        //Brain.Screen.newLine();
        //Brain.Screen.setCursor(2, 1);
        //Brain.Screen.print(a);

        // Set the speed and direction of the motors so that when we turn them on, the robot moves in the desired direction (the direction the joystick is pointing)

        setMotorSpeed(m1spd, FrontRightMotor);
        setMotorSpeed(m2spd, FrontLeftMotor);
        setMotorSpeed(m3spd, BackMotor);
      }

      /// \brief Set the orthogonal direction of the robot
      void SetOrthogonalDirection(int direction)
      {
        double x;
        double y;

        switch(direction)
        {
          case 0: x=0;  y=0;  break;
          case 1: x=0;  y=1;  break;
          case 2: x=0;  y=-1; break; 
          case 3: x=1;  y=0;  break;
          case 4: x=-1; y=0;  break;
        }

        // Calculate the angle between the x and y directional vectors to determine the direction the robot is to move
        double ang = atan2(y, x);
        // Calculate the magnitude that the robot movement needs to be from the x and y directional vectors
        double mag = sqrt(pow(y, 2) + pow(x, 2)); 
        // Set Front Right Wheel (motor 1) speed using wheel equation
        double m1spd = mag*cos(ang + M_PI/3); 
        // Set Front Left Wheel (motor 2) speed using wheel equation
        double m2spd = mag*cos(ang + 5*M_PI/3); 
        // Set Back Wheel (motor 3) speed using wheel equation
        double m3spd = mag*cos(ang + M_PI);

        setMotorSpeed(m1spd, FrontRightMotor);
        setMotorSpeed(m2spd, FrontLeftMotor);
        setMotorSpeed(m3spd, BackMotor);
      }

      /// \brief Sets the x-speed of the drivetrain
      void XSpeed(double x)
      {
        SetVelocity(x, YSpeedVar.Value(), AngleSpeedVar);
      }

      /// \brief Sets the y-speed of the drivetrain
      void YSpeed(double y)
      {
        SetVelocity(XSpeedVar.Value(), y, AngleSpeedVar);
      }

      /// \brief Sets the angular speed of the drivetrain
      void AngleSpeed(double a)
      {
        SetVelocity(XSpeedVar.Value(), YSpeedVar.Value(), a);
      }

      /// \brief Set the forward speed of the drivetrain
      void Forward(double d)
      {
        if (d>0) { SetOrthogonalDirection(1); }
      }

      /// \brief Set the backward speed of the drivetrain
      void Backward(double d)
      {
        if (d>0) { SetOrthogonalDirection(2); }
      }

      /// \brief Set the right speed of the drivetrain
      void Right(double d)
      {
        if (d>0) { SetOrthogonalDirection(3); }
      }

      /// \brief Set the left speed of the drivetrain
      void Left(double d)
      {
        if (d>0) { SetOrthogonalDirection(4); }
      }
    }
  }
}