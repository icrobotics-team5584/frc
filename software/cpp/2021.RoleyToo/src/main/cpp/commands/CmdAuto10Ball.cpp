// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdAuto10Ball.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
CmdAuto10Ball::CmdAuto10Ball(SubDriveBase* subDriveBase, SubIntake* subIntake, SubStorage* subStorage, SubTurret* subTurret) : _autonomous{
  [subDriveBase]{return subDriveBase->getYaw();}, 
  [subDriveBase]{return subDriveBase->getDistanceTravelled();}
} {
  AddCommands(
              frc2::SequentialCommandGroup{
                frc2::WaitCommand(3.0_s),
                CmdMoveStorage(subStorage, 0)
              },
              //CmdTrackTarget(subTurret),
              frc2::SequentialCommandGroup{
                //frc2::WaitCommand(6.0_s),
                frc2::PrintCommand{"home start ************"},
                CmdHomeTurret(subTurret),
                frc2::PrintCommand{"home end **************"},
                CmdTrackTarget(subTurret, subStorage)

              },
              frc2::SequentialCommandGroup{
                //frc2::InstantCommand([subStorage] {subStorage->Move(SubStorage::Direction::Forward, -0.8);}, {subStorage}),
                frc2::PrintCommand{"************LIAM WAS THIS IN THE RIOLOG??"},
                CmdAutoSetPose{&_autonomous, 1.7, -3.548,  0},
                CmdAutoIntakeDeploy(subIntake),
                CmdAutoShooterSpin(subTurret),
                frc2::PrintCommand{"shooter spin"},
                frc2::WaitCommand(3.0_s),
                CmdAutoFeederFeed(subStorage),
                frc2::WaitCommand(3.0_s),
                CmdAutoFeedStop(subStorage),
                
                CmdAutoTurn{subDriveBase, &_autonomous, PIDk{0.05, 0, 0}, -150, 30},
                
                
                //                                    startx, starty, endx, endy, endheading, cenx, ceny
                //CmdAutoIntakeDeploy(subIntake),
                frc2::InstantCommand([subIntake]{subIntake->Intake(1);}),

                CmdAutoDrive{subDriveBase, &_autonomous, 1.7, -4.048, 1.7, -8.053, 180, 0, 0, PIDk{-5, 0, -50}, 0.7, 0, PIDk{1, 0, 0}},
                CmdAutoTurn{subDriveBase, &_autonomous, PIDk{1, 0, 20}, 0, 20},
                CmdAutoDrive{subDriveBase, &_autonomous, 1.7, -8.053, 1.7, -4.548, 0, 0, 0, PIDk{-5, 0, -50}, 1, 0, PIDk{1, 0, 0}},
                frc2::InstantCommand([subIntake]{subIntake->Stop();}),
                
                CmdAutoFeederFeed(subStorage),
                frc2::WaitCommand(3.0_s),
                CmdAutoFeedStop(subStorage),
                //CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 8.053, -1.235, 9.46, 18.3, 0, 0, PIDk{-5, 0, -50}, 0.1, 0.1, PIDk{1, 0, 0}},
                //CmdAutoDrive{subDriveBase, &_autonomous, -1.7, 9.514, -1.7, 2.348, 180, 0, 0, PIDk{5, 0, 50}, 0.9, 0.0, PIDk{1, 0, 0}},

                
                CmdAutoShooterStop(subTurret)
                //CmdAutoTurn{subDriveBase, &_autonomous, PIDk{1, 0, 20}, 70, 20},
                //CmdAutoIntakeRetract(subIntake)
                
              }
              
              );
}
