// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Cmd1BallAuto.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include "Utilities/AutoPIDConfig.h"
#include "subsystems/SubStorage.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd1BallAuto::Cmd1BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage, Autonomous* autonomous)
{
  AddCommands(
    frc2::SequentialCommandGroup{
      CmdAutoSetPose{autonomous, subDriveBase, 0, 0, 0},
      
      // Set Shooter RPM to 2100rpm
      frc2::WaitCommand(5_s),
      // Run Storage 

      // Acuate Storage Pistons 

      frc2::WaitCommand(3_s),

      CmdAutoDrive{subDriveBase, autonomous, PIDAutoConfig{0, -0.5, 0, -2 , 0, 0, 0, PIDk{-1, 0, 0}, -0.2, 0, PIDk{1, 0, 0}}},
    }
  );
}