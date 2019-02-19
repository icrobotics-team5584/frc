/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdOutputPanel.h"
#include "Robot.h"
#include <frc/WPILib.h>


CmdOutputPanel::CmdOutputPanel() {
  // Use Requires() here to declare subsystem dependencies
  Requires(Robot::subPanelAffector.get());  
}

// Called just before this Command runs the first time
void CmdOutputPanel::Initialize() {
  Robot::subPanelAffector->DeployFingers();
  state = WAITING_FOR_FINGERS_OUT;
  timer.Start();
  timer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void CmdOutputPanel::Execute() {
  switch (state) {
    case WAITING_FOR_FINGERS_OUT:
      // Move on once we have waited for the fingers to deploy
      if (timer.Get() > FINGERS_WAIT_TIME) {
        Robot::subPanelAffector->Deploy();
        state = WAITING_FOR_BUTTON_RELEASE;
      }
      break;

    case WAITING_FOR_BUTTON_RELEASE:
      // Move on once the button is released
      if (!Robot::_oi->btnDeployPanel->Get()) {
        Robot::subPanelAffector->Retract();
        timer.Reset();
        state = WAITING_FOR_PUNCH_IN;
      }
      break;

    case WAITING_FOR_PUNCH_IN:
      // Move on once we have waited for the punches to retract
      if (timer.Get() > PUNCH_WAIT_TIME) {
        Robot::subPanelAffector->RetractFingers();
        state = FINISHED;
      }
      break;
    
    case FINISHED:
      // We are done, IsFinished will now return true and stop the command.
      timer.Stop();
      break;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdOutputPanel::IsFinished() {
  if (state == FINISHED) {
    return true;
  } else {
    return false;
  }
}

// Called once after isFinished returns true
void CmdOutputPanel::End() {
  // Everything has been retracted already by the time End runs. Check Execute()
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdOutputPanel::Interrupted() {
  End();
}
