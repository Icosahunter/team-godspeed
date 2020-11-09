using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision20__BLUE_BALL;
extern signature Vision20__RED_BALL;
extern signature Vision20__BACKBOARD;
extern signature Vision20__SIG_4;
extern signature Vision20__SIG_5;
extern signature Vision20__SIG_6;
extern signature Vision20__SIG_7;
extern vision Vision20;
extern bumper BumperA;
extern controller Controller1;
extern motor FrontRightMotor;
extern motor FrontLeftMotor;
extern motor BackMotor;
extern motor LeftCollectorMotor;
extern motor RightCollectorMotor;
extern motor ScorerMotor;
extern motor ballGuideMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );