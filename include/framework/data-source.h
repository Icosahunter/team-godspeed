#pragma once
#include "vex.h"
#include "event.h"

namespace godspeed
{
  namespace framework
  {
    /**
    * \brief An class representing a data source of an input device or internal object
    *
    * A particular input device may produce more than one piece of data, 
    * each piece of data will be a data source. The data will need to be 
    * represented as a double, even if it is more accurately an integer
    * or boolean.
    *
    * This class acts as an interface to objects that contain the DataSink object.
    */
    class DataSource
    {
      public:

        /// \brief The default constructor
        DataSource();

        /**
        * \brief The primary constructor, initializes all necessary values
        *
        * @param min The minimum value the data source will ever output
        * @param max The maximum value the data source will ever output
        * @param valFunc Address of a function that will return the current value of the data source
        * @param subscribeFunc Address of a function that will subscribe a given handler to value changes of the data source
        */
        DataSource(double min, double max, double (*valFunc)(void), void (*subscribeFunc)(void (*callback)(void)));

        /**
        * \brief The value getter for the data source
        */
        double (*value)(void);

        /**
        * \brief Function to subscribe to value changes of the source
        *
        * The subscribe attribute should contain a reference to a function 
        * that can receive an event handler and subscribe said handlers to 
        * value changes of the data source. This means that it can be used 
        * with any event framework that allows for handlers with no arguments
        * or returns.
        */
        void (*subscribe)(void (*callback)(void));

        /// \brief The maximum value the data source will have
        double maxValue();

        /// \brief The minimum value the data source will have
        double minValue();

        /**
        * \brief Rescales a data source value to be within a new min and max
        * 
        * This is used convert the data of a data source object into
        * a form that a data sink can receive. Specifically this is
        * used by the DataSinkD class.
        *
        * @param desiredMin The desired minimum value for the data
        * @param desiredMax The desired maximum value for the data
        * @param var The data source object to rescale the value of
        */
        static double rescale(double desiredMin, double desiredMax, DataSource &var);

        /**
        * \brief Converts the data from a data source to a boolean
        *
        * This is used convert the data of a data source object into
        * a form that a data sink can receive. Specifically this is
        * used by the DataSinkB class.
        *
        * Returns true if the value of the data source is greater
        * than half way between it's min and max. Otherwise returns
        * false.
        *
        * @param var The data source to convert the value of
        */
        static bool toBool(DataSource &var);

      private:

        /// \brief The maximum value the data source will have
        double max_ = 0;

        /// \brief The minimum value the data source will have
        double min_ = 0;
    };
  }
}