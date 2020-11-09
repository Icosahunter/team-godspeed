#include "framework/data-source.h"

namespace godspeed
{
  namespace framework
  {
    DataSource::DataSource()
    {
      
    }

    DataSource::DataSource(double min, double max, double (*valFunc)(void), void (*subscribeFunc)(void (*callback)(void)))
    {
      min_ = min;
      max_ = max;
      value = valFunc;
      subscribe = subscribeFunc;
    }

    double DataSource::minValue()
    {
      return min_;
    }

    double DataSource::maxValue()
    {
      return max_;
    }

    double DataSource::rescale(double desiredMin, double desiredMax, DataSource& dat)
    {
      double scaleFactor = (desiredMax - desiredMin) / (dat.maxValue() - dat.minValue());
      double shift = desiredMin - scaleFactor*dat.minValue();
      return scaleFactor*dat.value() + shift;
    }

    bool DataSource::toBool(DataSource& dat)
    {
      return rescale(0, 1, dat) > 0.5;
    }
  }
}