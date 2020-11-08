#include "framework/data-sink-d.h"

namespace godspeed
{
  namespace framework
  {
    DataSinkD::DataSinkD() : DataSink()
    {
      
    }

    DataSinkD::DataSinkD(double desMin, double desMax, void (*parentUpd)(void)) : DataSink(parentUpd)
    {
      desiredMin = desMin;
      desiredMax = desMax;
    }

    double DataSinkD::value()
    {
      return DataSource::rescale(desiredMin, desiredMax, *source_);
    }
  }
}