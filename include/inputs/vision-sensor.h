#pragma once
#include "vex.h"
#include "framework/smoothing.h"

namespace godspeed
{
  namespace inputs
  {
    /// \brief A namespace containing functions for accessing data from the Vision Sensor
    namespace VisionSensor
    {
      /// \brief Width of the screen in pixels
      double ScreenWidth = 314;

      /// \brief Height of the screen in pixels
      double ScreenHeight = 210;

      /// \brief Vertical field of view in radians
      double VerticalFOV = 20.3341 * (3.14/180);

      /// \brief Horizontal field of view in radians
      double HorizontalFOV = 30.2145 * (3.14/180);

      // Fine-tuning value to center the robot on the object instead of the camera
      double XOffsetFudge = 0;

      // Define in inches the width and height of a ball 
      double BallWidth = 6.3;
      double BallHeight = 6.3;

      // Define in inches the width and height of a goal's backboard
      double BackboardWidth = 4.375;
      double BackboardHeight = 6.1875;

      // Return the minimum of the set of values read by the Vision Sensor
      WinMin BallDistVar(50);
      WinMin GoalDistVar(50);

      // Return the average of the set of values read by the Vision Sensor
      WinAvg BallCountVar(10);
      WinAvg GoalCountVar(10);

      void Init()
      {
        BallDistVar.Initialize(infinity());
        GoalDistVar.Initialize(infinity());
      }

      /// \brief Calculated distance to an object, given it's dimensions etc.
      // The camera will always think that an object is farther away than it
      // actually is. However, the minimum of the ratio between the actual defined
      // size and the measured is the most accurate distance
      double CalculateDistance(double obj_w, double obj_h, double obj_x, double obj_w_actual, double obj_h_actual)
      {
        // Vertical component of the orthogonal distance to the object
        double orth_dist_v = ((obj_h_actual/obj_h)*ScreenHeight/2)/std::tan(VerticalFOV);
        // Horizontal component of the orthogonal distance to the object
        double orth_dist_h = ((obj_w_actual/obj_w)*ScreenWidth/2)/std::tan(HorizontalFOV);
        // Minimum calculated orthogonal distance to the object      
        double orth_dist = std::min(orth_dist_v, orth_dist_h);
        // Determine whether the height or the width makes the object look closer
        double ratio = std::min(obj_h_actual/obj_h, obj_w_actual/obj_w);
        // Determine the parallel component of the distance between the robot and the object
        double leg1 = ratio*obj_x + ratio*obj_w/2 - ratio*ScreenWidth/2;
        // Determine the orthogonal component of the distance between the robot and the object
        double leg2 = orth_dist;
        // Return the distance from the robot to the object
        return std::sqrt(std::pow(leg1, 2) + std::pow(leg2, 2));
      }

      /// \brief Calculated distance to the largest object given it's signature and actual width and height
      double GetDistance(signature sig, double obj_w, double obj_h)
      {
        // Capture a frame from the Vision Sensor
        Vision20.takeSnapshot(sig, 1);
        // Determine the largest object signature that matches the desired signature
        vision::object obj = Vision20.largestObject;

        // If the Vision Sensor identifies a signature, return its values
        if (obj.originX != 0)
        {
          return CalculateDistance(obj.width, obj.height, obj.originX, obj_w, obj_h);
        }

        // Otherwise return infinity
        else
        {
          return infinity();
        }
      }

      /// \brief Get the X offset of the largest object from the center of the screen, normalize to between -1 and 1
      double XOffset()
      {
        double d;
        if (Vision20.largestObject.centerX != 0.0)
        { d = 1 - Vision20.largestObject.centerX/(ScreenWidth/2) + XOffsetFudge; }
        else
        {  d = 0; }
        return d;
      }

      /// \brief Get the Y offset of the largest object from the center of the screen, normalize to between -1 and 1
      double YOffset()
      {
        double d;
        if (Vision20.largestObject.centerY != 0.0)
        { d = 1 - Vision20.largestObject.centerY/(ScreenHeight/2); }
        else
        {  d = 0; }
        return d;
      }

      /// \brief Returns the width, in pixels,  of the largest object
      double Size()
      {
        return Vision20.largestObject.width * Vision20.largestObject.height;
      }

      /**
      * \brief Returns the distance, in inches, to the largest ball found [NOT IMPLEMENTED]
      *
      * Take a snapshot looking for the ball, and then return Distance()
      */
      double BallDistance()
      {
        BallDistVar.SetValue(GetDistance(Vision20__RED_BALL, BallWidth, BallHeight));
        return BallDistVar.Value();
      }

      /** 
      * \brief Returns the X offset of the largest ball from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the ball, and then return XOffset()
      */
      double BallXOffset()
      {
        Vision20.takeSnapshot(Vision20__RED_BALL);
        return XOffset();
      }

      /** 
      * \brief Returns the Y offset of the largest ball from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the ball, and then return YOffset()
      */
      double BallYOffset()
      {
        Vision20.takeSnapshot(Vision20__RED_BALL);
        return YOffset();
      }

      /**
      * \brief Returns the number of balls found
      *
      * Take a snapshot looking for the ball
      */
      double BallCount()
      {
        BallCountVar.SetValue(Vision20.takeSnapshot(Vision20__RED_BALL));
        return std::ceil(BallCountVar.Value() - 0.5);
      }

      /**
      * \brief Returns the number of goals found
      *
      * Take a snapshot looking for the goal
      */
      double GoalCount()
      {
        GoalCountVar.SetValue(Vision20.takeSnapshot(Vision20__BACKBOARD));
        return std::ceil(GoalCountVar.Value() - 0.5);
      }

      /**
      * \brief Returns the distance, in inches, to the largest goal backboard icon found [NOT IMPLEMENTED]
      *
      * Take a snapshot looking for the goal, and then return Distance()
      */
      double GoalDistance()
      {
        GoalDistVar.SetValue(GetDistance(Vision20__BACKBOARD, BackboardWidth, BackboardHeight));
        return GoalDistVar.Value();
      }

      /** 
      * \brief Returns the X offset of the largest goal backboard icon from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the goal, and then return XOffset()
      */
      double GoalXOffset()
      {
        Vision20.takeSnapshot(Vision20__BACKBOARD);
        return XOffset();
      }

      /** 
      * \brief Returns the Y offset of the largest goal backboard icon from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the goal, and then return YOffset()
      */
      double GoalYOffset()
      {
        Vision20.takeSnapshot(Vision20__BACKBOARD);
        return YOffset();
      }
    }
  }
}