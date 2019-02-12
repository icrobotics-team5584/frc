#pragma once

#include <frc/commands/Command.h>

class CmdGimblePidCentre : public frc::Command {
 public:
  CmdGimblePidCentre();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
