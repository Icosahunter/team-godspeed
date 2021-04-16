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
  namespace ModeControl
  {
    enum robot { Robot_Bauble, Robot_Tchotchke };
    enum team { Team_Red, Team_Blue };
    enum mode { Autonomous_Mode, Driver_Control_Mode, Competition_Mode };

    robot Robot;
    team Team;
    mode Mode;
    competition Competition;
    void StartAutonomous();
    void StartDriverControl();
    void EndAutonomous();
    void EndDriverControl();
    void StartCompetition();
    void StartCompetitionTest();
    void StopRobot();

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
          EndAutonomous();
          EndDriverControl();
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