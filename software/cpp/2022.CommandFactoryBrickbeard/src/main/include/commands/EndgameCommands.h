#pragma once

#include <frc2/command/commands.h>
#include <frc2/command/button/CommandXboxController.h>

#include <units/length.h>

namespace cmd {
  frc2::CommandPtr ClimbSequence(frc2::CommandXboxController& controller);
  frc2::CommandPtr StartClimbSequence(frc2::CommandXboxController& controller);
  frc2::CommandPtr WaitForXButton(frc2::CommandXboxController& controller);
  frc2::CommandPtr ElevateTo(units::meter_t height);
  frc2::CommandPtr RotateClimbers();
  frc2::CommandPtr StowClimbers();
  frc2::CommandPtr ManualClimb(double speed);
  frc2::CommandPtr ToggleRotateClimbers();
};
