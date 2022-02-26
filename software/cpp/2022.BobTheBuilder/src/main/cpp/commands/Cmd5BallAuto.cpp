// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Cmd5BallAuto.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include "Utilities/AutoPIDConfig.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd5BallAuto::Cmd5BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous)
{
  AddCommands(
    frc2::SequentialCommandGroup{
      CmdAutoSetPose{autonomous, subDriveBase, 7.46, 1.86, 178.5},
      frc2::InstantCommand([subShooter] {subShooter->SetTargetRpm(2100);}),
      frc2::InstantCommand([subIntake] {subIntake->Intake(); }),
      frc2::InstantCommand([subStorage] {subStorage->ExtendStopper(); subStorage->In();}),
      frc2::InstantCommand([subIntake] {subIntake->Extend();}),

      CmdAutoDrive(subDriveBase, autonomous, auto5BallP1),
      frc2::WaitCommand(0.2_s),
      CmdAutoDrive(subDriveBase, autonomous, auto5BallP2),
      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, 20, 5},
      frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
      frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
      frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
      frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, -90, 5},
      CmdAutoDrive(subDriveBase, autonomous, auto5BallP3),
      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, 50, 5},
      frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
      frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, -90, 5},
      CmdAutoDrive(subDriveBase, autonomous, auto5BallP4),
      CmdAutoDrive(subDriveBase, autonomous, auto5BallP5),
      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, 67, 5},

      frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
      frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
      frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
      frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
      frc2::InstantCommand([subIntake] {subIntake->Retract(); subIntake->Stop(); }),
      frc2::InstantCommand([subStorage] {subStorage->Stop();}),
      frc2::InstantCommand([subShooter] {subShooter->SetShooterTracking(false);})
      
    }
  );
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
}
