#pragma once
#include "framework/data-source.h"

namespace godspeed
{
  namespace inputs
  {
    using namespace framework;

    /**
    * \brief A class containing data source objects corresponding to range finder inputs
    */
    class RangeFinder
    {
      public:
        /// \brief A data source corresponding to the distance measured
        static DataSource distance;

      private:
        static double distVal();
    };
  }
}
