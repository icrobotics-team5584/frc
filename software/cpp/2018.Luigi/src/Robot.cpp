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

std::shared_ptr<SubPnuematicOutput> Robot::subPnuematicOutput;

void Robot::RobotInit() {
	AutoChooser.AddObject("Default Auto", new MyAutoCommand());
	AutoChooser.AddObject("Pnuematic", new CmdPnuematicOutputOut());
	frc::SmartDashboard::PutData("Auto Modes", &AutoChooser);
	subPnuematicOutput.reset(new SubPnuematicOutput());
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

void AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void TeleopInit() {




//	if (Robot::m_autonomousCommand != nullptr) {
//		Robot::m_autonomousCommand->Cancel();
//		Robot::m_autonomousCommand = nullptr;
//	}
}

void TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void TestPeriodic() {

}



START_ROBOT_CLASS(Robot)
