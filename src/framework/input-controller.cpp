#include "framework/input-controller.h"

namespace godspeed
{
  namespace framework
  {

    std::list<InputDevice*> InputController::inputs_ = std::list<InputDevice*>();
    vex::thread InputController::thread_;
    bool InputController::isRunning_ = false;

    /**
    * The actual function handed to the thread to run
    *
    * This function loops through the overrided update() method as 
    * long as isRunning() returns true. The parameter it takes is 
    * a reference to the InputController. This is defined outside the 
    * class because you cannot run a class method on the thread object.
    */
    void InputController_upd()
    {
      while (InputController::isRunning())
      {
        InputController::update();
      }
    }

    void InputController::start()
    {
      if (!isRunning_)
      {
        isRunning_ = true;
        thread_ = vex::thread(InputController_upd);
      }
    }

    void InputController::update()
    {
      for (auto &input: inputs_)
      {
        input->update();
      }
    }

    void InputController::addInputDevice(InputDevice &input)
    {
      inputs_.push_back(&input);
    }

    void InputController::removeInputDevice(InputDevice &input)
    {
      //inputs_.remove(input);
    }

    void InputController::stop()
    {
      isRunning_ = false;
    }

    int32_t InputController::threadID()
    {
      return thread_.get_id();
    }

    bool InputController::isRunning()
    {
      return isRunning_;
    }

    void InputController::setPriority(int32_t priority)
    {
      thread_.setPriority(priority);
    }

    int32_t InputController::priority()
    {
      return thread_.priority();
    }

  }
}