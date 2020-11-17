#pragma once
#include "framework/data-sink-d.h"
#include "outputs/output-utilities.h"
#include "vex.h"

namespace godspeed
{
  namespace outputs
  {
    using namespace framework;
    using namespace outputUtilities;
    /**
    * \brief A class containing data sink objects corresponding to the ball collector
    *
    * This class contains a single data sink object that corresponds to
    * both collector arm treads. Currently does not allow for reverse direction.
    */
    class BallCollector
    {
      public:
        /**
        * The data sink for the velocity of the collector arm treads
        *
        * Does not allow for reverse direction
        */
        static DataSinkD collectorVelocity;

      private:
        /// The function to be called when a connected data source changes value
        static void update();

    };// end BallCollector
  }// end namespace outputs
}// end namespace godspeed