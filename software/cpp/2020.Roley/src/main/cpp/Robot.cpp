/*----------------------------------------------------------------------------*/
/*Robot.cpp                                                                   */
/*----------------------------------------------------------------------------*/

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

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


void Robot::RobotInit() {

  //Reset subsystems
  
  subDriveBase.reset(new SubDriveBase());
  subIntake.reset(new SubIntake());
  subShooter.reset(new SubShooter());
  subStorage.reset(new SubStorage());
  subClimber.reset(new SubClimber());
  subBuddyClimb.reset(new SubBuddyClimb());

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
  chooser.SetDefaultOption("Vanilla Trench Run", autoOne);
  chooser.AddOption("Trench Steal Run", autoTwo);
  chooser.AddOption("Sad Trench Run", autoThree);
  frc::SmartDashboard::PutData("Auto Selecter", &chooser);

  frc::SmartDashboard::PutData("Dolly Deploy", new CmdDeployDolly());
}


void Robot::RobotPeriodic() {

  frc::SmartDashboard::PutNumber("Match Time", timer->GetMatchTime());
  frc::SmartDashboard::PutNumber("Left RPM", subShooter->GetLeftRPM());
  frc::SmartDashboard::PutNumber("Right RPM",subShooter->GetRightRPM());
  //subShooter->speed = frc::SmartDashboard::GetNumber("Motor Speed", subShooter->speed);
  //frc::SmartDashboard::PutNumber("Motor Speed", subShooter->speed);
  posEncoderGyro->updateAbsolutePosition();
  posEncoderGyro->updateRelativePosition();
  //std::cout << "update position" << std::endl;
}


void Robot::DisabledInit() {}


void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }


void Robot::AutonomousInit() {
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
  subDriveBase->retractDolly();
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
