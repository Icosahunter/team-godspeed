#pragma once
#include "vex.h"
#include "event.h"

namespace godspeed
{
  /**
  * An class representing a data source of an input device
  *
  * A particular input device may produce more than
  * one piece of data, each piece of data will be a data source.
  * The data will need to be represented as a float.
  */
  class DataSource
  {
    public:

      DataSource();

      DataSource(double min, double max, double (*valFunc)(void), void (*subscribeFunc)(void (*callback)(void)));

      /**
      * The value getter for the data source
      */
      double (*value)(void);

      /**
      * Function to subscribe to value changes of the source
      */
      void (*subscribe)(void (*callback)(void));

      /**
      * The maximum value the data source will have
      */
      double maxValue();

      /**
      * The minimum value the data source will have
      */
      double minValue();

      static double rescale(double desiredMin, double desiredMax, DataSource &var);
      static bool toBool(DataSource &var);

    private:

      double max_ = 0;
      double min_ = 0;
  };
}