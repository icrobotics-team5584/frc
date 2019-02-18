#pragma once

#include <frc/commands/Command.h>

class CmdDriveBaseSlow : public frc::Command {
 public:
  CmdDriveBaseSlow(bool reversed);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
  bool _reversed;

  double x;
  double y;
  double axis;
};
