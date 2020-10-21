using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision1__BLUE_BALL;
extern signature Vision1__RED_BALL;
extern signature Vision1__BACKBOARD;
extern signature Vision1__SIG_4;
extern signature Vision1__SIG_5;
extern signature Vision1__SIG_6;
extern signature Vision1__SIG_7;
extern vision Vision1;
extern bumper BumperA;
extern controller Controller1;
extern motor Motor1;
extern motor Motor2;
extern motor Motor3;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );