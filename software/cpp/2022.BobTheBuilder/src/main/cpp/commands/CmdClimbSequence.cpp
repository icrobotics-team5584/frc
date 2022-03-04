// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdClimbSequence.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/WaitUntilCommand.h>
#include <subsystems/SubClimber.h>
#include <frc2/command/PrintCommand.h>
#include <frc2/command/WaitCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
CmdClimbSequence::CmdClimbSequence(SubClimber* subClimber, frc::XboxController* xboxController) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand(), BarCommand());
  AddCommands(
  //stow arms
  frc2::InstantCommand([&] { subClimber->Stow(); }),
  frc2::WaitCommand(1_s),
  frc2::PrintCommand("Stowed"),

  //retract arms
  frc2::InstantCommand([&] { subClimber->Retract(); }),
  frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Retract"),
  //wait 
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("Pressed x"),
  //extend
  frc2::InstantCommand([&] { subClimber->Extend(); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Extended"),
  //retract 
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Retract(); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Retract"),
  //slightly extend
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->DriveTo(SubClimber::NEAR_MIN_POS); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("near min pos"),
  //rotate arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] {subClimber->Rotate(); }),
  frc2::WaitCommand(1_s),
  frc2::PrintCommand("Rotated"),
  //extand arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Extend(); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("extended"),
  //stow arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Stow(); }),
  frc2::WaitCommand(1_s),
  frc2::PrintCommand("Stowed"),
  //retact amrs
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Retract(); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Retract"),
  //slighty extend
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->DriveTo(SubClimber::NEAR_MIN_POS); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Near min pos"),
  //rotate arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] {subClimber->Rotate(); }),
  frc2::WaitCommand(1_s),
  frc2::PrintCommand("Rotate"),
  //extend arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Extend(); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Extended"),

  //stow arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Stow(); }),
  frc2::WaitCommand(1_s),
  frc2::PrintCommand("Stowed"),
  //retract arms
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->Retract(); }),
   frc2::WaitUntilCommand([&] {return subClimber->IsAtTargetPosition(); }),
  frc2::PrintCommand("Retract"),
  //slightly extend
  frc2::WaitUntilCommand([&] {return xboxController->GetXButton(); }),
  frc2::PrintCommand("pressed x"),
  frc2::InstantCommand([&] { subClimber->DriveTo(SubClimber::NEAR_MIN_POS); }),
  frc2::PrintCommand("near min pos")
  );
  }
