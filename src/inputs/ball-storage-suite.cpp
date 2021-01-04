#include "inputs/ball-storage-suite.h"

namespace godspeed
{
  namespace inputs
  {
    DataSource BallStorage::ballsStored = DataSource(0,4, ballNumVal, ballNumSubscribe);

    double BallStorage::ballNumVal(){
        return ballCount;
    }
    void BallStorage::ballNumSubscribe(void (*callback)(void)){
        BumperA.pressed(callback);
        BumperB.pressed(callback);
     }
     void BallStorageUpdate::bumperBUpdate(void (*callback)(void)){
      BumperB.released(callback);
      BallStorage::ballCount--;
     }
     void BallStorageUpdate::bumperAUpdate(void (*callback)(void)){
      BumperA.released(callback);
      BallStorage::ballCount--;
     }
  }
}
