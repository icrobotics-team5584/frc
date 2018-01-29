#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "SmartDashboard/SmartDashboard.h"

//Include Autonomous Commands
#include "Commands/CmdAutonomous.h"

//Include Subsystems
#include "Subsystems/SubDriveBase.h"
#include "Subsystems/SubIntake.h"
#include "Subsystems/SubEncodedArmLift.h"
#include "Subsystems/SubCameras.h"

#include "OI.h"

class Robot : public frc::TimedRobot {
public:
	int intAutonomousTask = 0;

	frc::Command* autonomousCommand = nullptr;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	frc::SendableChooser<frc::Command*> autoChooser;

	static std::unique_ptr<OI> oi;
	static std::shared_ptr<SubDriveBase> subDriveBase;
	static std::shared_ptr<SubIntake> subIntake;
	static std::shared_ptr<SubEncodedArmLift> subEncodedArmLift;
	static std::shared_ptr<SubCameras> subCameras;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;

	static std::shared_ptr<MotionProfileData> MPData;

};
#endif
