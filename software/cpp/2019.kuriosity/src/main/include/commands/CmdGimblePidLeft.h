#pragma once

#include <frc/commands/Command.h>

class CmdGimblePidLeft : public frc::Command {
 public:
  CmdGimblePidLeft();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
