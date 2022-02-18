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
#include <frc2/command/WaitUntilCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd2BallAuto::Cmd2BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous){
  AddCommands(
    frc2::SequentialCommandGroup{
      CmdAutoSetPose{autonomous, subDriveBase, 0, 0, 0},
      CmdAutoDrive{subDriveBase, autonomous, autoRoutineOneLegOne},
      frc2::WaitCommand(0.5_s),

      CmdAutoTurn{subDriveBase, autonomous, PIDk{0.1, 0, 0.6 }, 180, 5},
      CmdAutoDrive{subDriveBase, autonomous, autoRoutineOneLegTwo},
      frc2::WaitUntilCommand([subShooter]{return subShooter->IsAtTargetSpeed();}),
      // Acuate Storage Pistons
      frc2::WaitCommand(3_s),
      
      CmdAutoDrive{subDriveBase, autonomous, autoRoutineOneLegThree},
      CmdSpinUpShooter{subShooter, 0},
      


    },
    CmdIntake{subIntake}.WithTimeout(5_s),
    CmdDeployIntake{subIntake}.WithTimeout(15_s),
    CmdStorageIn{subStorage}.WithTimeout(15_s),
    CmdSpinUpShooter{subShooter, 2100}
  );

}
