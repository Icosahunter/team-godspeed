#include "inputs/range-finder.h"

namespace godspeed
{
  namespace inputs
  {
    DataSource RangeFinder::distance = DataSource(30, 3000, distVal);


    double RangeFinder::distVal() {
        return (double)RangeFinder1.distance(mm); 
        }

  }
}
