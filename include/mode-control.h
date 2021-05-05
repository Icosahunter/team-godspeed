#pragma once
#include "vex.h"
#include "outputs/omni-drive-3-wheel.h"
#include "outputs/ball-collector.h"
#include "outputs/ball-scorer.h"
#include "framework/binder.h"
#include "autonomous/state-machine.h"
#include "bauble/autonomous.h"
#include "bauble/driver-control.h"
#include "tchotchke/autonomous.h"
#include "tchotchke/driver-control.h"
#include "inputs/ball-storage.h"
#include "inputs/vision-sensor.h"

namespace godspeed
{
  /// \brief A namespace for controlling the operation of the robot
  namespace ModeControl
  {
    enum robot { Robot_Bauble, Robot_Tchotchke };
    enum team { Team_Red, Team_Blue };
    enum mode { Autonomous_Mode, Driver_Control_Mode, Competition_Mode };

    /// \brief Set this depending on the robot being used (Robot_Tchotchke or Robot_Bauble)
    robot Robot;

    /// \brief Set this depending on the team color (Team_Red, Team_Blue)
    team Team;

    /// \brief Set this depending on the desired operation mode (Autonomous_Mode, Driver_Control_Mode, Competition_Mode)
    mode Mode;
    competition Competition;

    /// \brief Starts autonomous mode
    void StartAutonomous();

    /// \brief Starts driver control mode
    void StartDriverControl();

    /// \brief Disables autonomous mode
    void EndAutonomous();

    /// \brief Disables driver control mode
    void EndDriverControl();

    /// \brief Starts competition watcher to watch for field control events and change mode appropriately
    void StartCompetition();

    void StartCompetitionTest();
    
    /// \brief Stops the robots movement
    void StopRobot();

    /// \brief Start the mode controller (set Robot, Team, and Mode before calling this)
    void Init()
    {
      // Initializations
      Binder::Init();
      outputs::BallScorer::Init();
      inputs::BallStorage::Init();
      inputs::VisionSensor::Init();
      Brain.resetTimer();

      Competition.bStopAllTasksBetweenModes = false;
      Competition.bStopTasksBetweenModes = false;

      if (Mode == Competition_Mode)
      {
        StartCompetition();
      }
      else if (Mode == Autonomous_Mode)
      {
        StartAutonomous();
      }
      else if (Mode == Driver_Control_Mode)
      {
        StartDriverControl();
      }
    }

    /// \brief Thread function of competition watcher thread
    void CompetitionWatcher()
    {
      while (true)
      {
        if (Competition.AUTONOMOUS)
        {
          EndDriverControl();
          StartAutonomous();
        }
        else if (Competition.DRIVER_CONTROL)
        {
          EndAutonomous();
          StartDriverControl();
        }
        else if (Competition.DISABLED)
        {
          // EndAutonomous();
          // EndDriverControl();
        }
        this_thread::yield();
      }
    }

    void StartCompetition()
    {
      // Competition Setup
      thread t(CompetitionWatcher);
      t.detach();
    }

    void StartAutonomous()
    {
      StateMachine::Init();

      if (Team == Team_Red)
      {
        inputs::VisionSensor::BallSig = &Vision20__RED_BALL;
      }
      else
      {
        inputs::VisionSensor::BallSig = &Vision20__BLUE_BALL;
      }

      if (Robot == Robot_Bauble)
      {
        Bauble::StartAutonomous();
      }
      else
      {
        Tchotchke::StartAutonomous();
      }
    }

    void StopRobot()
    {
      StateMachine::Kill();
      if (StateMachine::tptr != nullptr)
      {
        StateMachine::tptr->join();
      }
      Binder::ClearBindings();
      outputs::OmniDrive3Wheel::Stop();
      outputs::BallCollector::Stop();
      outputs::BallScorer::Stop();
    }

    void EndAutonomous()
    {
      StopRobot();
    }

    void StartDriverControl()
    {
      if (Robot == Robot_Bauble)
      {
        Bauble::BindDriverControl();
      }
      else
      {
        Tchotchke::BindDriverControl();
      }
    }

    void EndDriverControl()
    {
      StopRobot();
    }
  }
}