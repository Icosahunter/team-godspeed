#pragma once
#include "framework/data-source.h"

namespace godspeed
{
  namespace inputs
  {
    using namespace framework;

    /**
    * \brief A class containing data source objects corresponding to ball storage suite inputs
    */
    class BallStorage
    {
      public:
        /// \brief A data source corresponding to the balls stored within the robot and an int for increment var
        static DataSource ballsStored;
        static int ballCount;

      private:
        static double ballNumVal(); 

        static void bumperASubscribe(void (*callback)(void));
        static void bumperBSubscribe(void (*callback)(void));

        static void ballNumSubscribe(void (*callback)(void));
    };
    /**
    * \brief A class containing the functions to update the ballCount
    */
    class BallStorageUpdate
    {
      private:
      static void bumperAUpdate(void (*callback)(void));
      static void bumperBUpdate(void (*callback)(void));
    };
  }
}