#include <algorithm>
#include <numeric>
#include <list>

namespace godspeed
{
    class Smoothing
    {
      public:

        double Value()
        {
          return std::accumulate(values.begin(), values.end(), 0.0)/values.size();
        }

        void SetValue(double val)
        {
          values.pop_back();
          values.push_front(val);
        }

        Smoothing(int winsize = 100)
        {
          values.resize(winsize);
        }

      private:
        std::list<double> values;
    };
}