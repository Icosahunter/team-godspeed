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

    class BallScorer
    {
      public:
        static DataSinkD scorerVelocity;
        static DataSinkD ballGuideExpander;

      private:
        /// The function to be called when a connected data source changes value
        static void update();

    };// end BallScorer
  }// end namespace outputs
}// end namespace godspeed