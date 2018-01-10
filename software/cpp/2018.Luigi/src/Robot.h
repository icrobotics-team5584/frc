#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "Commands/Command.h"
#include "LiveWindow/LiveWindow.h"
#include "SmartDashboard/SendableChooser.h"
#include "SmartDashboard/SmartDashboard.h"
#include <OI.h>

//Include Subsystems
#include <Subsystems/SubPnuematicOutput.h>
#include <Subsystems/SubDriveBase.h>
#include <Subsystems/SubIntake.h>

//Include Commands
#include <Commands/CmdPnuematicOutputOut.h>
#include <Commands/MyAutoCommand.h>
#include <Subsystems/SubDriveBase.h>

class Robot : public frc::TimedRobot {
public:
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();

	static std::unique_ptr<OI> oi;

	//Create Pointers to Subsystems
	static std::shared_ptr<SubPnuematicOutput> subPnuematicOutput;
	static std::shared_ptr<SubDriveBase> subDriveBase;
	static std::shared_ptr<SubIntake> subIntake;

	frc::SendableChooser<frc::Command*> AutoChooser;
	std::shared_ptr<frc::Command> AutoCommand;


//	static sfrc::Command* m_autonomousCommand = nullptr;
//	static MyAutoCommand m_myAuto;
//	static frc::SendableChooser<frc::Command*> m_chooser;

private:

};



#endif /* SRC_ROBOT_H_ */
