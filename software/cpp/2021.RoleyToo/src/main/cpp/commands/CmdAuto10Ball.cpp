// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAuto10Ball.h"
#include <frc2/command/InstantCommand.h>
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
CmdAuto10Ball::CmdAuto10Ball(SubDriveBase* subDriveBase, SubIntake* subIntake) : _autonomous{
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
} {
  AddCommands(CmdAutoSetPose{&_autonomous, -1.7, 3.548,  0},
              //                                    startx, starty, endx, endy, endheading, cenx, ceny
              CmdAutoIntakeDeploy(subIntake),
              frc2::InstantCommand([subIntake]{subIntake->Intake(1);}),
              CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 4.048, -1.7, 9.514, 0, 0, 0, PIDk{-5, 0, -50}, 0.75, 0, PIDk{1, 0, 0}},
              frc2::InstantCommand([subIntake]{subIntake->Stop();}),
              CmdAutoIntakeRetract(subIntake)
              //CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 7.048, -1.7, 4.048, 0, 0, 0, PIDk{-1, 0, -20}, -1, 0, PIDk{-0.6, 0, 0}}
              //CmdAutoTurn{subDriveBase, &_autonomous, PIDk{1, 0, 20}, 180, 10}
              //CmdAutoDrive{subDriveBase, &_autonomous, 6.548, -1.7, 3.348,-1.7, 180, 0, 0, PIDk{3.2, 0, 20}, 0.1}
              );
}
