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
        /// \brief A data source corresponding to the distance measured
        static DataSource ballStorage;

      private:
        static double ballStorageVal();
        static void ballStorageSubscribe(void (*callback)(void));
        int bumpACount;
        int bumpBCount;
    };
  }
}