// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Cmd3BallAuto.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include "Utilities/AutoPIDConfig.h"
#include "commands/CmdIntake.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdRetractIntake.h"
#include "commands/CmdStorageIn.h"
#include "commands/CmdSpinUpShooter.h"
#include "commands/CmdTrackTarget.h"
#include <frc2/command/WaitUntilCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd3BallAuto::Cmd3BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());

  AddCommands(
    CmdAutoSetPose{autonomous, subDriveBase, 7.46, 1.86, 178.5},
    frc2::InstantCommand([subShooter] {subShooter->SetShooterTracking(false);}),
    //first ball speed
    frc2::InstantCommand([subShooter] {subShooter->SetTargetRpm(500);}),
    frc2::InstantCommand([subIntake] {subIntake->Intake(); }),
    frc2::InstantCommand([subStorage] {subStorage->ExtendStopper(); subStorage->In();}),
    frc2::InstantCommand([subIntake] {subIntake->Extend();}),
    CmdAutoDrive(subDriveBase, autonomous, auto5BallP1),
    frc2::WaitCommand(0.2_s),
    CmdAutoDrive(subDriveBase, autonomous, auto5BallP2),    
    frc2::InstantCommand([subIntake] {subIntake->Retract(); subIntake->Stop(); }),
    CmdAutoDrive(subDriveBase, autonomous, auto5BallP3),
    CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, 55, 1},
    frc2::InstantCommand([subIntake] {subIntake->Extend();}),
    frc2::InstantCommand([subIntake] {subIntake->Intake(); }),
    frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
    frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
    
    frc2::ParallelCommandGroup{
      frc2::SequentialCommandGroup{
        frc2::WaitCommand(0.3_s),
        frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
        //second ball speed
        frc2::InstantCommand([subShooter] {subShooter->SetTargetRpm(500);}),
        frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
        frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
        frc2::WaitCommand(0.3_s),
        frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();})
      },
      CmdAutoDrive(subDriveBase, autonomous, auto5BallP4)

    },
    frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
    frc2::InstantCommand([subStorage] {subStorage->RetractStopper();}),
    frc2::WaitCommand(0.3_s),

    
    frc2::InstantCommand([subStorage] {subStorage->ExtendStopper();}),
    frc2::InstantCommand([subIntake] {subIntake->Retract(); subIntake->Stop(); }),
    frc2::InstantCommand([subStorage] {subStorage->Stop();}),
    frc2::InstantCommand([subShooter] {subShooter->SetShooterTracking(false);}),
    frc2::InstantCommand([subShooter] {subShooter->Stop();})
  );

}
