// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Cmd5BallAuto.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include "Utilities/AutoPIDConfig.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd5BallAuto::Cmd5BallAuto(SubDriveBase* subDriveBase, SubIntake* subIntake, SubShooter* subShooter, SubStorage* subStorage) : _autonomous {  
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
}{
  AddCommands(
    frc2::SequentialCommandGroup{
      CmdAutoSetPose{&_autonomous, subDriveBase, 0, 0, 90},
      frc2::WaitCommand(2_s),
      //set shooter velocity to 2100rpm
      CmdAutoDrive(subDriveBase, &_autonomous, auto5BallP3),
      CmdAutoTurn(subDriveBase, &_autonomous, PIDk{0.1, 0, 0}, 180, 5),
      // CmdAutoDrive(subDriveBase, &_autonomous, auto5BallP4),
    }
  );
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
}
