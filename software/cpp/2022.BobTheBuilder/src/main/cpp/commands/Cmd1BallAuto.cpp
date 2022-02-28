// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Cmd1BallAuto.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include "Utilities/AutoPIDConfig.h"
#include "subsystems/SubStorage.h"
#include "commands/CmdTrackTarget.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd1BallAuto::Cmd1BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous)
{
  AddCommands(
    frc2::SequentialCommandGroup{
      CmdAutoSetPose{autonomous, subDriveBase, 0, 0, 0},
      frc2::InstantCommand([subShooter] { subShooter->SetShooterTracking(true); }),
      frc2::InstantCommand([subIntake] {subIntake->Extend(); }),
      frc2::InstantCommand([subStorage] { subStorage->In(); }), 
      CmdAutoDrive{subDriveBase, autonomous, PIDAutoConfig{0, -0.5, 0, -2 , 0, 0, 0, PIDk{-1, 0, 0}, -0.2, 0, PIDk{1, 0, 0}}},
      CmdTrackTarget(subDriveBase, subShooter),
      frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] { subStorage->Stop(); }),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
      frc2::InstantCommand([subIntake] {subIntake->Retract(); })
    }
  );
}