#include "framework/input-variable.h"

namespace godspeed
{
  namespace framework
  {
    InputVariable::InputVariable()
    {
      
    }

    InputVariable::InputVariable(double min, double typical, double max)
    {
      min_ = min;
      typical_ = typical;
      max_ = max;
    }

    double InputVariable::minValue()
    {
      return min_;
    }

    double InputVariable::typicalValue()
    {
      return typical_;
    }

    double InputVariable::maxValue()
    {
      return max_;
    }

    double InputVariable::rescale(double desiredMin, double desiredMax, InputVariable& var)
    {
      double scaleFactor = (desiredMax - desiredMin) / (var.maxValue() - var.minValue());
      double shift = desiredMin - var.minValue();
      return scaleFactor*var.value() + shift;
    }

    bool InputVariable::toBool(InputVariable& var)
    {
      return rescale(0, 1, var) > 0.5;
    }
  }
}