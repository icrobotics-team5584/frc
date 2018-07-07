/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CmdAutoDrive.h"
#include <iostream>

CmdAutoDrive::CmdAutoDrive(double Distance, double Angle) {
	Requires(Robot::subDriveBase.get());
	_Distance = Distance;
	_Angle = Angle;
}

// Called just before this Command runs the first time
void CmdAutoDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CmdAutoDrive::Execute() {
	Robot::subDriveBase->AutoDrive(0.5, _Angle);
}

// Make this return true when this Command no longer needs to run execute()
bool CmdAutoDrive::IsFinished() {
	double Meters;
	Meters = Robot::subDriveBase->GetEncoderDistance();

	std::cout << "Meters Travelled: " << Meters << std::endl;
	std::cout << "SetDistance: " << _Distance << std::endl;

	if (Meters >= _Distance){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void CmdAutoDrive::End() {
	Robot::subDriveBase->AutoDrive(0.000, 0);
	Robot::subDriveBase->ResetEncoder();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdAutoDrive::Interrupted() {
	End();
}
