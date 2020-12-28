#include "inputs/range-finder.h"

namespace godspeed
{
  namespace inputs
  {
    DataSource RangeFinder::distance = DataSource(30, 3000, distVal, distValSubscribe);


    double RangeFinder::distVal() {
        return (double)RangeFinder1.distance(mm); 
        }
     void RangeFinder::distValSubscribe(void (*callback)(void)) {
        RangeFinder1.changed(callback);
        }
  }
}