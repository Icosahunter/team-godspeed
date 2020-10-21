#pragma once
#include "vex.h"
#include "framework/data-source.h"
#include "framework/data-sink.h"

namespace godspeed
{

  class DataSinkB : public DataSink
  {
    public:
      DataSinkB();
      DataSinkB(void (*parentUpd)(void));
      bool value();
  };

}