#pragma once
#include "vex.h"
#include "outputs/ball-scorer.h"
#include "framework/binder.h"

namespace godspeed
{
  namespace Tchotchke
  {
    double expander_pos() { return 355; }
    Binding ExpanderBinding(expander_pos, outputs::BallScorer::ExpanderPosition);
  }
}