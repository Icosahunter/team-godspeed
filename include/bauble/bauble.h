#pragma once
#include "vex.h"
#include "outputs/ball-scorer.h"
#include "framework/binder.h"

namespace godspeed
{
  /// \brief A namespace containing the state machine and driver control code for the Bauble robot
  namespace Bauble
  {
    double expander_pos() { return 345; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);
  }
}