#pragma once
#include "vex.h"
#include "framework/data-source.h"

namespace godspeed
{

  class DataSink
  {
    public:
      DataSink();
      DataSink(void (*parentUpd)(void));
      void connect(DataSource &dat);
      void (*parentUpdate)(void);

    protected:
      DataSource* source_;
      
  };

}