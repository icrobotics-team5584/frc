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

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
Cmd2BallAuto::Cmd2BallAuto(SubDriveBase* subDriveBase) : _autonomous {  
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
}{
  AddCommands(
    frc2::SequentialCommandGroup{
      CmdAutoSetPose{&_autonomous, 0.1, 0, 0},
      frc2::WaitCommand(6.1_s),
      CmdAutoDrive{subDriveBase, &_autonomous, autoRoutineOneLegOne}
      // 1.7 - 
    }
  );

}
