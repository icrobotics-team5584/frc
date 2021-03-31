// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAuto10Ball.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
CmdAuto10Ball::CmdAuto10Ball(SubDriveBase* subDriveBase, SubIntake* subIntake) : _autonomous{
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
} {
  AddCommands(/*
              CmdAutoSetPose{&_autonomous, 3.545, -1.7, 0},
              //                                    startx, starty, endx, endy, endheading, cenx, ceny
              CmdAutoDrive{subDriveBase, &_autonomous, 3.548, -1.7, 9.014,-1.7, 0, 0, 0, PIDk{3.2, 0, 20}, 0.1},
              */
              CmdAutoSetPose{&_autonomous, 8.514, -1.7, 0},
              //                                    startx, starty, endx, endy, endheading, cenx, ceny
              CmdAutoDrive{subDriveBase, &_autonomous, 8.514, -1.7, 9.014,-1.7, 0, 0, 0, PIDk{3.2, 0, 20}, 0.1}
              );
}
