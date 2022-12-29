#include "RobotContainer.h"
#include "commands/BallCommands.h"
#include "commands/DriveCommands.h"
#include "commands/EndgameCommands.h"
#include "commands/AutoCommands.h"

#include "subsystems/SubDrivebase.h"
#include "subsystems/SubIntake.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubStorage.h"
#include "subsystems/SubClimber.h"

#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  SubDrivebase::GetInstance().SetDefaultCommand(cmd::JoystickDrive(_controller));
  SubShooter::GetInstance().SetDefaultCommand(cmd::AccelerateFlyweelToTarget());
  SubStorage::GetInstance();
  SubClimber::GetInstance();
  SubIntake::GetInstance();

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  using namespace frc2::cmd;

  // Configure your button bindings here
  _controller.RightBumper().WhileTrue(cmd::Intake());
  _controller.LeftBumper().WhileTrue(cmd::AimAndShootTwice());
  
  _controller.Start().OnTrue(cmd::StartClimbSequence(_controller));
  _controller.Y().WhileTrue(cmd::ManualClimb(0.5));
  _controller.A().WhileTrue(cmd::ManualClimb(-0.5));
  _controller.B().ToggleOnTrue(cmd::ToggleRotateClimbers());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return cmd::PPDrivePath();
}
