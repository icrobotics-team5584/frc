#pragma once

#include <frc/commands/Command.h>

class CmdElevatorLimit : public frc::Command {
 public:
  CmdElevatorLimit();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
