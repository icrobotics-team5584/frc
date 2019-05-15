#pragma once

#include <frc/commands/Command.h>

class CmdClimberLatch : public frc::Command {
 public:
  CmdClimberLatch();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
