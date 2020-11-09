#include "outputs/ball-scorer.h"

namespace godspeed 
{
  namespace outputs
  {
    DataSinkD BallScorer::scorerVelocity = DataSinkD(0, 1, update);
    DataSinkD BallScorer::ballGuideExpander = DataSinkD(1, 1, update);
    void BallScorer::update()
    {
      setMotorSpeed(scorerVelocity.value(), ScorerMotor);
    }
  }// end namespace outputs
}// end namespace godspeed