#pragma once
#include "vex.h"
#include "framework/data-source.h"
#include "framework/data-sink.h"

namespace godspeed
{

  class DataSinkD : public DataSink
  {
    public:
      DataSinkD();
      DataSinkD(double desMin, double desMax, void (*parentUpd)(void));
      double value();
      double desiredMin;
      double desiredMax;
  };

}