#include "Robot.h"
#include <Commands/Scheduler.h>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>

shared_ptr<SubDriveBase> Robot::subDriveBase;
shared_ptr<OI> Robot::oi;
shared_ptr<RobotMap> Robot::robotMap;

void Robot::RobotInit() {
    robotMap.reset(new RobotMap());

    // Create Subsystems after robotMap so subsystems can use devices from robotMap
    subDriveBase.reset(new SubDriveBase());

    // Create OI after subsystems so commands can use their required subsystems
    oi.reset(new OI());

    // Begin loading pure persuit path as soon as robot is on.
    cmdMakePath.reset(new CmdMakePath);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * Runs once at the beginning of autonomous. Use this to handle autonomous
 * mode selection.
 */
void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
    //Zero sensors
    subDriveBase->zeroEncoders();
    subDriveBase->zeroGyro();

    cmdMakePath->Start();
}

void Robot::TeleopPeriodic() { 
    frc::Scheduler::GetInstance()->Run(); 
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
START_ROBOT_CLASS(Robot)
#endif
