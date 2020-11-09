#include "outputs/output-utilities.h"
#include <cmath>

namespace godspeed
{
  namespace outputs
  {
    namespace outputUtilities
    {
      void setMotorSpeed(double motorSpeed, motor &m)
      {
        // if motor speed is out of bounds, set to nearest boundary value
        if (std::abs(motorSpeed) > 1)
        {
          m.setVelocity(100, percentUnits::pct);
          m.spin(forward);
        }
        // if motor speed is out of bounds, set to nearest boundary value
        else if (std::abs(motorSpeed) > 0.1)
        {
          m.setVelocity(100*motorSpeed, percentUnits::pct);
          m.spin(forward);
        }
        else
        {
          m.stop();
        }
        
      }// end setMotorSpeed
    }// end namespace outputUtilities
  }// end namespace outputs
}// end namespace godspeed
