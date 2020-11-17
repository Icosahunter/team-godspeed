#pragma once
#include "vex.h"
#include "framework/data-source.h"
#include "framework/data-sink.h"

namespace godspeed
{
  namespace framework
  {
    /**
    * \brief An class representing a data sink of an output device or internal object
    *
    * This is an implementation of a data source for the boolean data type.
    */
    class DataSinkB : public DataSink
    {
      public:

        /// \brief The default constructor
        DataSinkB();

        /**
        * \brief The primary constructor
        *
        * @param parentUpd A function to call whenever the value of the connected data source changes
        */
        DataSinkB(void (*parentUpd)(void));

        /// \brief The value of the attached data source converted to a boolean
        bool value();
    };
  }
}