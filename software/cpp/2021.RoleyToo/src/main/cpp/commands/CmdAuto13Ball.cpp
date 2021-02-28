// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAuto13Ball.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/co     nvenience-features.html
CmdAuto13Ball::CmdAuto13Ball(SubDriveBase* subDriveBase) : _autonomous{
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
} {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(CmdAutoSetPose{&_autonomous, 0, -0.4, 0},
              CmdAutoDrive{subDriveBase, &_autonomous, 0,0,-1.5,1.5,-90,-1.5,0, PIDk{-3.2, 0, -20}, 0.1},
              CmdAutoDrive{subDriveBase, &_autonomous, -1.5,1.5,-2.35,1.5,-90,-1.5,1.5,PIDk{-3.2, 0, -20},0.1},
              CmdAutoDrive{subDriveBase, &_autonomous, -1.5,1.5,0,0,180,-1.5,0, PIDk{3.2, 0, 20}, -0.1},
              CmdAutoDrive{subDriveBase, &_autonomous, 0,0,0,-0.85,180,0,0, PIDk{3.2, 0, 20}, -0.1}
              );

}
