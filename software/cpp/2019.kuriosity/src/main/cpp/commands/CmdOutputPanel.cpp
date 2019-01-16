/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdOutputPanel.h"
#include "Robot.h"
#include <frc/WPILib.h>


CmdOutputPanel::CmdOutputPanel(bool autoHold) {
  // Use Requires() here to declare subsystem dependencies
  _autoHold = autoHold;
  Requires(Robot::subPanelAffector.get());
  
}

// Called just before this Command runs the first time
void CmdOutputPanel::Initialize() {
  notDeployed = true;
  if (_autoHold == true){
    SmartDashboard::PutNumber("Test", SmartDashboard::GetNumber("Pneumatic_hold", 0.0));
    SetTimeout(SmartDashboard::GetNumber("Pneumatic_hold", 0.3));
    SmartDashboard::PutNumber("Pneumatic_hold", timeoutTime);
  }

  Robot::subPanelAffector->DeployFingers();
  cout << "Deploy Fingers" << endl;
  _timer.Reset();
  _timer.Start();	
}

// Called repeatedly when this Command is scheduled to run
void CmdOutputPanel::Execute() {
  if((_timer.Get() > 1) && notDeployed){
    Robot::subPanelAffector->Deploy();
    cout << "Deploy Hatch" << endl;
    notDeployed = false;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool CmdOutputPanel::IsFinished() { 
 if(IsTimedOut()){
   return true;
 }
  return false; 
}

// Called once after isFinished returns true
void CmdOutputPanel::End() {
  Robot::subPanelAffector->Retract();
  cout << "Retract Hatch" << endl;
  _timer.Reset();
  _timer.Start();	
  while(_timer.Get() < 1){
  }
  Robot::subPanelAffector->RetractFingers();
  cout << "Retract Fingers" << endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdOutputPanel::Interrupted() {
  End();
}
