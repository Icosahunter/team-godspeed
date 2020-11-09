#include "outputs/ball-collector.h"

namespace godspeed 
{
  namespace outputs
  {
    DataSinkD BallCollector::collectorVelocity = DataSinkD(0, 1, update);

    void BallCollector::update()
    {
      setMotorSpeed(collectorVelocity.value(), LeftCollectorMotor);
      setMotorSpeed(collectorVelocity.value(), RightCollectorMotor);
    }
  }// end namespace outputs
}// end namespace godspeed