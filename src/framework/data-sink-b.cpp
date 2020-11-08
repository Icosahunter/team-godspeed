#include "framework/data-sink-b.h"

namespace godspeed
{
  namespace framework
  {
    DataSinkB::DataSinkB() : DataSink()
    {

    }

    DataSinkB::DataSinkB(void (*parentUpd)(void)) : DataSink(parentUpd)
    {

    }

    bool DataSinkB::value()
    {
      return DataSource::toBool(*source_);
    }
  }
}