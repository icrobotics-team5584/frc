/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

unique_ptr<OI> Robot::_oi;
unique_ptr<RobotMap> Robot::_robotMap;
unique_ptr<SubDriveBase> Robot::subDriveBase;
unique_ptr<SubElevator> Robot::subElevator;
unique_ptr<SubTurret> Robot::subTurret;
unique_ptr<SubPanelAffector> Robot::subPanelAffector;
unique_ptr<SubIntakeOutake> Robot::subIntakeOutake;
unique_ptr<SubRollerIntake> Robot::subRollerIntake;

void Robot::RobotInit() {
  
  _robotMap.reset(new RobotMap);

    subDriveBase.reset(new SubDriveBase());
    subElevator.reset(new SubElevator());
    subTurret.reset(new SubTurret());
    subIntakeOutake.reset(new SubIntakeOutake());
    subPanelAffector.reset(new SubPanelAffector());
    subRollerIntake.reset(new SubRollerIntake());

    _oi.reset(new OI);
    std::cout << "robot init finish" << std::endl;

    SmartDashboard::PutBoolean("started running End()", false);
    SmartDashboard::PutBoolean("started running backwards()", false);
    SmartDashboard::PutBoolean("finished running backwards()", false);

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
    SmartDashboard::PutNumber("Navx Yaw", subDriveBase->getYaw());
    SmartDashboard::PutNumber("Bottom Ultrasonic", subDriveBase->getDistanceToObstical());
    SmartDashboard::PutBoolean("front sensor", subDriveBase->frontHasReachedLine());
    SmartDashboard::PutBoolean("mid sensor", subDriveBase->midHasReachedLine());
    SmartDashboard::PutBoolean("left sensor", subDriveBase->isLeftClsOnLine());
    SmartDashboard::PutBoolean("right sensor", subDriveBase->isRightClsOnLine());
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

    cmdSeekCargoShip.reset(new CmdSeekCargoShip());

    cmdSeekCargoShip->Start();
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
  frc::Scheduler::GetInstance()->Run();
  bool buttonPressed;
  SmartDashboard::PutBoolean("Go back", buttonPressed);
  SmartDashboard::GetBoolean("Go back", buttonPressed);
  if (buttonPressed) {
    Robot::subDriveBase->drive(-0.5, 0);
  }
}

void Robot::TeleopInit() {
    subDriveBase->resetYaw();
}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
