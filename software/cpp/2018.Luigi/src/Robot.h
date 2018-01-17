#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

//Include Commands
#include "Commands/AutonomousCommand.h"
#include "Commands/CmdAutoForward.h"
#include "Commands/CmdAutoBackward.h"

//Include Subsystems
#include "Subsystems/SubDriveBase.h"
#include "Subsystems/SubIntake.h"
#include "Subsystems/SubArmLift.h"
#include "Subsystems/SubEncodedArmLift.h"

#include "OI.h"

class Robot : public frc::TimedRobot {
public:

	std::string gameData;

	frc::Command* autonomousCommand = nullptr;
	static std::unique_ptr<OI> oi;
	frc::LiveWindow *lw = frc::LiveWindow::GetInstance();
	frc::SendableChooser<frc::Command*> chooser;

	static std::shared_ptr<SubDriveBase> subDriveBase;
	static std::shared_ptr<SubIntake> subIntake;
	static std::shared_ptr<SubArmLift> subArmLift;
	static std::shared_ptr<SubEncodedArmLift> subEncodedArmLift;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
};
#endif
