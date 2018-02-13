#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "SmartDashboard/SmartDashboard.h"
#include "OI.h"

//Include Autonomous Options
#include "Commands/CmdAutonomous.h"
#include "Autonomous/AutonomousSelector.h"
#include "Autonomous/GameData.h"
#include "Commands/AutonomousCommands/CmdAuto_Left_Switch_Left.h"

//Include Subsystems
#include "Subsystems/SubDriveBase.h"
#include "Subsystems/SubIntake.h"
#include "Subsystems/SubEncodedArmLift.h"
#include "Subsystems/SubCameras.h"
#include "Subsystems/SubRamp.h"

class Robot : public frc::TimedRobot {
public:

	//Declare objects for autonomous selection
	static GameData gameData;
	static AutonomousSelector autoSelector;
	static std::shared_ptr<MotionProfileData> MPData;

	//Decalre operator interface
	static std::unique_ptr<OI> oi;

	//Declare subsystems
	static std::shared_ptr<SubDriveBase> subDriveBase;
	static std::shared_ptr<SubIntake> subIntake;
	static std::shared_ptr<SubEncodedArmLift> subEncodedArmLift;
	static std::shared_ptr<SubCameras> subCameras;
	static std::shared_ptr<SubRamp> subRamp;

	//Declare robot functions
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
};

#endif
