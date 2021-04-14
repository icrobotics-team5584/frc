// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAuto10Ball.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/PrintCommand.h>
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
CmdAuto10Ball::CmdAuto10Ball(SubDriveBase* subDriveBase, SubIntake* subIntake, SubStorage* subStorage) : _autonomous{
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
} {
  AddCommands(
              CmdMoveStorage(subStorage, 9750),
              frc2::SequentialCommandGroup{
                //frc2::InstantCommand([subStorage] {subStorage->Move(SubStorage::Direction::Forward, -0.8);}, {subStorage}),
                
                CmdAutoSetPose{&_autonomous, -1.7, 3.548,  0},
                //                                    startx, starty, endx, endy, endheading, cenx, ceny
                CmdAutoIntakeDeploy(subIntake),
                frc2::InstantCommand([subIntake]{subIntake->Intake(1);}),

                CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 4.048, -1.7, 8.128, 0, 0, 0, PIDk{-5, 0, -50}, 0.8, 0.5, PIDk{1, 0, 0}},
                
                
                CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 8.128, -1.43, 9.028, 16.7, 0, 0, PIDk{-5, 0, -50}, 0.5, 0.2, PIDk{1, 0, 0}},
                //CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 9.514, -1.7, 2.348, 180, 0, 0, PIDk{5, 0, 50}, 0.9, 0.0, PIDk{1, 0, 0}},

                frc2::InstantCommand([subIntake]{subIntake->Stop();}),
                //CmdAutoTurn{subDriveBase, &_autonomous, PIDk{1, 0, 20}, 70, 20},
                //CmdAutoIntakeRetract(subIntake)
              }
              
              );
}
