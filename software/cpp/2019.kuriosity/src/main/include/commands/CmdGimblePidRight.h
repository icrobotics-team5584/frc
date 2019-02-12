#pragma once

#include <frc/commands/Command.h>

class CmdGimblePidRight : public frc::Command {
 public:
  CmdGimblePidRight();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
