// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Util/AutonomousSelector.h"
#include "Util/GameData.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommand.h"
#include "Subsystems/SubDriveBase.h"
#include "Subsystems/SubIntake.h"
#include "Subsystems/SubEncodedArm.h"
#include "Subsystems/SubCamera.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"

class Robot : public frc::TimedRobot {
public:


	frc::Command* autonomousCommand = nullptr;
	static std::unique_ptr<OI> oi;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	frc::SendableChooser<frc::Command*> chooser;
	static std::shared_ptr<SubDriveBase> subDriveBase;
	static std::shared_ptr<SubIntake> subIntake;
	static std::shared_ptr<SubEncodedArm> subEncodedArm;
	static std::shared_ptr<SubCamera> subCamera;


	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;

private:
	AutonomousSelector autoSel;
	GameData gamedata;
	static std::shared_ptr<Command> chosenCommand;
};
#endif
