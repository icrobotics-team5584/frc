/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <TimedRobot.h>
#include <Robot.h>
#include <OI.h>

std::shared_ptr<SubPnuematicOutput> Robot::subPnuematicOutput;
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<SubIntake> Robot::subIntake;

std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
	//Setup Autonomous Chooser
	AutoChooser.AddObject("Default Auto", new MyAutoCommand());
	frc::SmartDashboard::PutData("Auto Modes", &AutoChooser);

	//Initialize Subsystems
	subPnuematicOutput.reset(new SubPnuematicOutput());
	subDriveBase.reset(new SubDriveBase());
	subIntake.reset(new SubIntake());

	//Initialize Out/In
	oi.reset(new OI());
}

void Robot::DisabledInit() {

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	AutoCommand.reset(AutoChooser.GetSelected());
	if (AutoCommand.get() != nullptr) {
		AutoCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	if (AutoCommand.get() != nullptr) {
		AutoCommand->Cancel();
		AutoCommand = nullptr;
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {

}

START_ROBOT_CLASS(Robot)
