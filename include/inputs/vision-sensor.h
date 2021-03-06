#pragma once
#include "vex.h"

namespace godspeed
{
  namespace inputs
  {
    /// \brief A namespace containing functions for accessing data from the Vision Sensor
    namespace VisionSensor
    {
      /// \brief Width of the screen in pixels
      double ScreenWidth = 315;

      /// \brief Height of the screen in pixels
      double ScreenHeight = 210;

      double ballCount = 0;
      double goalCount = 0;

      /// \brief Smoothing applied to ball counting
      double CountSmoothing = 0.125;

      double ballSize = 0;
      double goalSize = 0;

      /// \brief Smoothing applied to size of largest object
      double SizeSmoothing = 0.5;

      /**
      * \brief Take a snapshot, looking for the given signature
      *
      * This function also prints an 'x' on the controller screen
      * at the location of the center of the largest object recognized
      * in the snapshot.
      */
      int Snapshot(signature sig)
      {
        int c = Vision20.takeSnapshot(sig);
        int x = Vision20.largestObject.centerX/5;
        int y = Vision20.largestObject.centerY/5;
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(y, x);
        Controller1.Screen.print("x");
        return c;
      }

      /// \brief Get the X offset of the largest object from the center of the screen, normalize to between -1 and 1
      double XOffset()
      {
        double d;
        if (Vision20.largestObject.centerX != 0.0)
        { d = 1 - Vision20.largestObject.centerX/(ScreenWidth/2); }
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

      /// \brief Returns the distance, in inches, to the largest object [NOT IMPLEMENTED]
      double Distance()
      {
        return 0;
      }

      /**
      * \brief Returns the distance, in inches, to the largest ball found [NOT IMPLEMENTED]
      *
      * Take a snapshot looking for the ball, and then return Distance()
      */
      double BallDistance()
      {
        Snapshot(Vision20__RED_BALL);
        return Distance();
      }

      /** 
      * \brief Returns the X offset of the largest ball from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the ball, and then return XOffset()
      */
      double BallXOffset()
      {
        Snapshot(Vision20__RED_BALL);
        return XOffset();
      }

      /** 
      * \brief Returns the Y offset of the largest ball from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the ball, and then return YOffset()
      */
      double BallYOffset()
      {
        Snapshot(Vision20__RED_BALL);
        return YOffset();
      }

      /**
      * \brief Returns the width, in pixels, of the largest ball found
      *
      * Take a snapshot looking for the ball, then call Size() and apply smoothing based on the last value found
      */
      double BallSize()
      {
        Snapshot(Vision20__RED_BALL);
        double s = Size();
        ballSize = SizeSmoothing*ballSize + (1-SizeSmoothing)*s;
        return ballSize;
      }

      /**
      * \brief Returns width, in pixels, of the largest goal backboard icon found
      *
      * Take a snapshot looking for the goal, then call Size() and apply smoothing based on the last value found
      */
      double GoalSize()
      {
        Snapshot(Vision20__BACKBOARD);
        double s = Size();
        goalSize = SizeSmoothing*goalSize + (1-SizeSmoothing)*s;
        return goalSize;
      }

      /**
      * \brief Returns the number of balls found
      *
      * Take a snapshot looking for the ball, take the number of objects found and apply smoothing based on the last count
      */
      double BallCount()
      {
        int n = Snapshot(Vision20__RED_BALL);
        ballCount = CountSmoothing*ballCount + (1-CountSmoothing)*n;
        return ballCount;
      }

      /**
      * \brief Returns the number of goals found
      *
      * Take a snapshot looking for the goal, take the number of objects found and apply smoothing based on the last count
      */
      double GoalCount()
      {
        int n = Snapshot(Vision20__BACKBOARD);
        goalCount = CountSmoothing*goalCount + (1-CountSmoothing)*n;
        return goalCount;
      }

      /**
      * \brief Returns the distance, in inches, to the largest goal backboard icon found [NOT IMPLEMENTED]
      *
      * Take a snapshot looking for the goal, and then return Distance()
      */
      double GoalDistance()
      {
        Snapshot(Vision20__BACKBOARD);
        return Distance();
      }

      /** 
      * \brief Returns the X offset of the largest goal backboard icon from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the goal, and then return XOffset()
      */
      double GoalXOffset()
      {
        Snapshot(Vision20__BACKBOARD);
        return XOffset();
      }

      /** 
      * \brief Returns the Y offset of the largest goal backboard icon from the center of the screen, normalize to between -1 and 1
      *
      * Take a snapshot looking for the goal, and then return YOffset()
      */
      double GoalYOffset()
      {
        Snapshot(Vision20__BACKBOARD);
        return YOffset();
      }
    }
  }
}