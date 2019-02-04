#pragma once

#include <frc/commands/Command.h>

class CmdDriveBaseSlow : public frc::Command {
 public:
  CmdDriveBaseSlow();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
