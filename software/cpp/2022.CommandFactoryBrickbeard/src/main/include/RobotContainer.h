#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/CommandXboxController.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::CommandPtr GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  frc2::CommandXboxController _controller{0};

  void ConfigureButtonBindings();
};
