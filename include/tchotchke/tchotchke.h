#pragma once
#include "vex.h"
#include "outputs/ball-scorer.h"
#include "framework/binder.h"

namespace godspeed
{
  /// \brief A namespace containing the state machine and driver control code for the Tchotchke robot
  namespace Tchotchke
  {
    double expander_pos() { return 355; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);
  }
}