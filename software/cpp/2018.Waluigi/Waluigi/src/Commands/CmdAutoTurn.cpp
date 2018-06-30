/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdAutoTurn.h"
#include "../Robot.h"

CmdAutoTurn::CmdAutoTurn(double Angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::subDriveBase.get());
	_Angle = Angle;

}

// Called just before this Command runs the first time
void CmdAutoTurn::Initialize() {
	Robot::subDriveBase->SetSetpoint(_Angle);
}
// Called repeatedly when this Command is scheduled to run
void CmdAutoTurn::Execute() {


}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoTurn::IsFinished() {

	return Robot::subDriveBase->AtSetpoint();



}

// Called once after isFinished returns true
void CmdAutoTurn::End() {
	Robot::subDriveBase->PIDEnd();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoTurn::Interrupted() {
	End();
}
