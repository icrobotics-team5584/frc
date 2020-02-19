/*----------------------------------------------------------------------------*/
/*Robot.cpp                                                                   */
/*----------------------------------------------------------------------------*/

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>

#include "commands/CmdDeployDolly.h"
#include "commands/CmdElevatorPowerDown.h"
#include "commands/CmdElevatorPowerUp.h"
#include "commands/CmdEngageClimberRatchets.h"
#include "commands/CmdBuddyDeploy.h"
#include "commands/CmdBuddyLock.h"
#include "commands/CmdIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdStorageTogglePneumatic.h"
#include "commands/CmdRollStorage.h"
#include "commands/CmdRollStorageBack.h"
#include "commands/CmdShooterShoot.h"
#include "commands/CmdShooterShootReverse.h"

#include "Robot.h"

std::shared_ptr<SubShooter> Robot::subShooter;
std::shared_ptr<SubStorage> Robot::subStorage;
std::shared_ptr<SubIntake> Robot::subIntake;
std::shared_ptr<SubDriveBase> Robot::subDriveBase;
std::shared_ptr<PosEncoderGyro> Robot::posEncoderGyro;
std::shared_ptr<CmdResetGyro> Robot::cmdResetGyro;
std::shared_ptr<SubClimber> Robot::subClimber;
std::shared_ptr<SubBuddyClimb> Robot::subBuddyClimb;
std::shared_ptr<frc::Timer> Robot::timer;
std::unique_ptr<OI> Robot::oi;
std::shared_ptr<TalonSRX> Robot::doubleTalon;

void Robot::RobotInit() {

  //Reset subsystems
  std::cout << "robot init" << std::endl;
  doubleTalon.reset(new TalonSRX(can_srxIntake));
  subDriveBase.reset(new SubDriveBase());
  std::cout << "after subdrivebase created" << std::endl;
  subIntake.reset(new SubIntake());
  std::cout << "after subintake constructor" << std::endl;

  subShooter.reset(new SubShooter());
  subStorage.reset(new SubStorage());
  subClimber.reset(new SubClimber());
  subBuddyClimb.reset(new SubBuddyClimb());

  
  std::cout << "after double talon created" << std::endl;
  
  timer.reset(new frc::Timer());
  //Reset Auto Encoder
  posEncoderGyro.reset(new PosEncoderGyro());
  //Auto CMD Reset
  cmdResetGyro.reset(new CmdResetGyro());
  autoOne = new CmdAutoRoutineOne();
  autoTwo = new CmdAutoRoutineTwo();
  autoThree = new CmdAutoRoutineThree();
  //Auto INIT process
  oi.reset(new OI());
  posEncoderGyro->reset();
  //Enable cmd yaw to be run without being cancelledo
  cmdResetGyro->SetRunWhenDisabled(true);
  //Runs a cmd that waits for th navx to stop calibrating then resets gyro
  cmdResetGyro->Start();
  chooser.SetDefaultOption("Six Ball Auto", autoOne);
  chooser.AddOption("Trench Steal Run", autoTwo);
  chooser.AddOption("Sad Trench Run", autoThree);
  frc::SmartDashboard::PutData("Auto Selecter", &chooser);


/*------------------------------------------------------------------------*/
/* Hardware testing control.                                              */
/* "PutData" push up commands used to test most hardware features on the  */
/*  robot.                                                                */  
/*------------------------------------------------------------------------*/
  //DRIVEBASE ----------------------------------------------------------------
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdDeployDolly", *(new CmdDeployDolly()));
  //ELEVATOR ----------------------------------------------------------------
  //NOTE: Currently not integrated. DO NOT USE!
  //frc::Shuffleboard::GetTab("HARDWARE").Add("CmdElevatorPowerUp", *(new CmdElevatorPowerUp())); 
  //frc::Shuffleboard::GetTab("HARDWARE").Add("CmdElevatorPowerDown", *(new CmdElevatorPowerDown())); 
  //frc::Shuffleboard::GetTab("HARDWARE").Add("CmdEngageClimberRatchets", *(new CmdEngageClimberRatchets()));  
  //BUDDY ----------------------------------------------------------------
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdBuddyLock", *(new CmdBuddyLock()));
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdBuddyDeploy", *(new CmdBuddyDeploy()));
  //INTAKE ----------------------------------------------------------------
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdIntake", *(new CmdIntake()));
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdOuttake", *(new CmdOuttake()));
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdDeployIntake", *(new CmdDeployIntake()));
  //STORAGE ----------------------------------------------------------------
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdStorageTogglePneumatic", *(new CmdStorageTogglePneumatic()));
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdRollStorage", *(new CmdRollStorage()));
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdRollStorageBack", *(new CmdRollStorageBack()));
  //SHOOTER ----------------------------------------------------------------
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdShooterShoot", *(new CmdShooterShoot()));
  frc::Shuffleboard::GetTab("HARDWARE").Add("CmdShooterShootReverse", *(new CmdShooterShootReverse()));

}


void Robot::RobotPeriodic() {
  frc::SmartDashboard::PutBoolean("lbrTopStorage", Robot::subStorage->GetLbrTopStorage());
  frc::SmartDashboard::PutNumber("Match Time", timer->GetMatchTime());
  frc::SmartDashboard::PutNumber("Left RPM", subShooter->GetLeftRPM());
  frc::SmartDashboard::PutNumber("Right RPM",subShooter->GetRightRPM());
  frc::SmartDashboard::PutBoolean("ShooterShoot", CmdShooterShoot::ShooterShoot);
  //subShooter->speed = frc::SmartDashboard::GetNumber("Motor Speed", subShooter->speed);
  //frc::SmartDashboard::PutNumber("Motor Speed", subShooter->speed);
  posEncoderGyro->updateAbsolutePosition();
  posEncoderGyro->updateRelativePosition();
  //std::cout << "update position" << std::endl;
  
}


void Robot::DisabledInit() {}


void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }


void Robot::AutonomousInit() {
  subDriveBase->autoConfig();
  autoOne = new CmdAutoRoutineOne();
  autoTwo = new CmdAutoRoutineTwo();
  autoThree = new CmdAutoRoutineThree();

  if (autonomousCommand != nullptr){
    autonomousCommand->Cancel();
  }
  autonomousCommand = chooser.GetSelected();
  if (autonomousCommand != nullptr){
    frc::SmartDashboard::PutString("Chosen auto command", autonomousCommand->GetName());
    autonomousCommand->Start();
  }
  // autoTwo->Start();
  subDriveBase->deployDolly();
}

void Robot::AutonomousPeriodic() { 
  std::cout << "auto start scheduler run" << std::endl;

  frc::Scheduler::GetInstance()->Run();
  std::cout << "auto end scheduler run" << std::endl;
    
  }

void Robot::TeleopInit() {
  subDriveBase->teleConfig();
  subDriveBase->retractDolly();
  subClimber->RatchetsDisengage();
  subClimber->ElevaterExtendMin();
  subBuddyClimb->Forward();
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
}


void Robot::TeleopPeriodic() { 
  
  frc::Scheduler::GetInstance()->Run(); 
  }

void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
