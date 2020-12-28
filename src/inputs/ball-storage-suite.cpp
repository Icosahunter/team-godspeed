#include "inputs/ball-storage-suite.h"

namespace godspeed
{
  namespace inputs
  {
    DataSource BallStorage::ballStorage = DataSource(0, 4, ballStorageVal, ballStorageSubscribe);


    double BallStorage::ballStorageVal() {
        if (BumperA.pressing())
          bumpACount++;
        if (BumperB.pressing())
          bumpBCount++;

        return (double)(bumpBCount-bumpACount); 
        }
     void BallStorage::ballStorageSubscribe(void (*callback)(void)) {
        BumperA.pressed(void (*callback)(void));
        BumperA.released(void (*callback)(void));
        BumperB.pressed(void (*callback)(void));
        BumperB.released(void (*callback)(void));
        }
  }
}