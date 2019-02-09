/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <cameraserver/CameraServer.h>
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

unique_ptr<OI> Robot::_oi;
unique_ptr<RobotMap> Robot::_robotMap;
unique_ptr<SubDriveBase> Robot::subDriveBase;
unique_ptr<SubElevator> Robot::subElevator;
unique_ptr<SubElevatorLimits> Robot::subElevatorLimits;
unique_ptr<SubPanelAffector> Robot::subPanelAffector;
unique_ptr<SubIntakeOutake> Robot::subIntakeOutake;
unique_ptr<SubRollerIntake> Robot::subRollerIntake;
unique_ptr<SubGimble> Robot::subGimble;

void Robot::RobotInit() {
  _robotMap.reset(new RobotMap);

    
    subDriveBase.reset(new SubDriveBase());
    subElevator.reset(new SubElevator());
    subElevatorLimits.reset(new SubElevatorLimits());
    subIntakeOutake.reset(new SubIntakeOutake());
    subPanelAffector.reset(new SubPanelAffector());
    subRollerIntake.reset(new SubRollerIntake());
    subGimble.reset(new SubGimble());
    cam = CameraServer::GetInstance()->StartAutomaticCapture();
    cam.SetResolution(90, 80);
    // cam.SetFPS(20);

    // server = CameraServer::GetInstance()->GetServer();
    // server.SetSource(cam);
    _oi.reset(new OI);

    // m_chooser.SetDefaultOption("Default Auto", &m_defaultAuto);
    // m_chooser.AddOption("My Auto", &m_myAuto);
    // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
    SmartDashboard::PutNumber("Yaw", subDriveBase->getYaw());
    SmartDashboard::PutNumber("Elevator encoder", subElevator->GetEncoderPosition());
    SmartDashboard::PutBoolean("On Line", subDriveBase->clsBackRightDetected());
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {


    // std::string autoSelected = frc::SmartDashboard::GetString(
    //     "Auto Selector", "Default");
    // if (autoSelected == "My Auto") {
    //   m_autonomousCommand = &m_myAuto;
    // } else {
    //   m_autonomousCommand = &m_defaultAuto;
    // }

    // m_autonomousCommand = m_chooser.GetSelected();

    //  if (m_autonomousCommand != nullptr) {
    //   m_autonomousCommand->Start();
    // }
}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
    Robot::subElevator->SetHeight(BOTTOM_HATCH);
    subDriveBase->resetYaw();

}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
