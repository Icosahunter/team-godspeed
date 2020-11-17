#pragma once
#include "vex.h"
#include "framework/data-source.h"

namespace godspeed
{
  namespace framework
  {
    /**
    * \brief An class representing a data sink of an output device or internal object
    *
    * A particular output device may require more than one input to 
    * control it, each of these inputs will be a data sink object.
    * This is an incomplete class as it doesn't have a value getter.
    * This class is extended by other data sinks with particular associated 
    * data types.
    *
    * This class acts as an interface to objects that contain the DataSource object.
    */
    class DataSink
    {
      public:
        /// \brief The default constructor
        DataSink();

        /**
        * \brief The primary constructor
        *
        * @param parentUpd A function to call whenever the value of the connected data source changes
        */
        DataSink(void (*parentUpd)(void));

        /**
        * \brief Connects this data sink to a data source object
        *
        * @param dat the data source to connect to
        */
        void connect(DataSource &dat);

        /// \brief A reference to a function to call whenever the value of the connected data source changes
        void (*parentUpdate)(void);

      protected:
        /// \brief A reference to the connected data source object
        DataSource* source_;
        
    };
  }
}