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
    * This is an implementation of a data source for the double data type.
    */
    class DataSinkD : public DataSink
    {
      public:
        /// \brief The default constructor
        DataSinkD();

        /**
        * \brief The primary constructor
        *
        * @param desMin The desired minimum for the value() function to return
        * @param desMax The desired maximum for the value() function to return
        * @param parentUpd A function to call whenever the value of the connected data source changes
        */
        DataSinkD(double desMin, double desMax, void (*parentUpd)(void));

        /// \brief The scaled value of the attached data source
        double value();

        /// \brief The desired minimum for the value() function to return
        double desiredMin;

        /// \brief The desired maximum for the value() function to return
        double desiredMax;
    };
  }
}