// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Cmd2BallAuto.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
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
Cmd2BallAuto::Cmd2BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous){
  AddCommands(
      CmdAutoSetPose{autonomous, subDriveBase, 0, 0, 0},
frc2::InstantCommand([subShooter] {subShooter->SetShooterTracking(true);}),

      frc2::InstantCommand([subIntake] {subIntake->Extend(); }),
      frc2::InstantCommand([subStorage] { subStorage->In(); }), 
      frc2::InstantCommand([subIntake] {subIntake->Intake();}),
      CmdAutoDrive{subDriveBase, autonomous, autoRoutineOneLegOne},
      frc2::WaitCommand(0.2_s),
      CmdAutoDrive{subDriveBase, autonomous, autoRoutineOneLegTwo},
      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, 180, 5},
      CmdAutoDrive{subDriveBase, autonomous, autoRoutineOneLegThree},
      CmdTrackTarget(subDriveBase, subShooter),
      frc2::WaitUntilCommand([subShooter]{return subShooter->IsAtTargetSpeed();}),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
      frc2::WaitUntilCommand([subShooter]{return subShooter->IsAtTargetSpeed();}),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
      frc2::WaitUntilCommand([subShooter]{return subShooter->IsAtTargetSpeed();}),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
      frc2::WaitUntilCommand([subShooter]{return subShooter->IsAtTargetSpeed();}),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.3_s),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),


      frc2::InstantCommand([subIntake] {subIntake->Retract(); }),
      frc2::InstantCommand([subStorage] { subStorage->Stop(); }),
      frc2::InstantCommand([subIntake] { subIntake->Stop();}),
      frc2::InstantCommand([subShooter] { subShooter->SetShooterTracking(false); }),
      frc2::InstantCommand([subShooter] {subShooter->Stop();})
      
      
  );

}
