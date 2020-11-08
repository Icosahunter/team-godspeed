#include "framework/data-sink.h"

namespace godspeed
{
  namespace framework
  {
    DataSink::DataSink()
    {
      
    }

    DataSink::DataSink(void (*parentUpd)(void))
    {
      parentUpdate = parentUpd;
    }

    void DataSink::connect(DataSource &dat)
    {
      source_ = &dat;
      dat.subscribe(parentUpdate);
    }
  }
}