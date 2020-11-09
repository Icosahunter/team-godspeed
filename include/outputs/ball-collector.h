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

    class BallCollector
    {
      public:
        static DataSinkD collectorVelocity;

      private:
        /// The function to be called when a connected data source changes value
        static void update();

    };// end BallCollector
  }// end namespace outputs
}// end namespace godspeed