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
    * \brief A class containing data sink objects corresponding to the ball scorer
    *
    * This class contains two data sink objects, one for the center tread and one
    * for the ball guide expander. Currently does not allow reverse direction.
    */
    class BallScorer
    {
      public:
        /**
        * \brief The data sink for the velocity of the center (ball scorer) tread
        *
        * Does not allow for reverse direction
        */
        static DataSinkD scorerVelocity;

        /**
        * \brief The data sink for the ball guide expander
        *
        * The guide expander is a linear actuator that should initiate
        * at the begining of a match. Currently the min and max of this
        * object are both set to 1 as a temporary patch for not having
        * support for setting a constant value data source.
        */
        static DataSinkD ballGuideExpander;

      private:
        /// \brief The function to be called when a connected data source changes value
        static void update();

    };// end BallScorer
  }// end namespace outputs
}// end namespace godspeed