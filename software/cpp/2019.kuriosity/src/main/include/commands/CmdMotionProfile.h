#pragma once

#include <frc/commands/Command.h>
#include "motionProfile/MotionProfileControl.h"
#include "motionProfile/MotionProfileData.h"

class CmdMotionProfile : public frc::Command {
 public:
  CmdMotionProfile();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
private:
  std::shared_ptr<MotionProfileData> mpData;
  std::unique_ptr<MotionProfileControl> mpControl;
  std::shared_ptr<WPI_TalonSRX> _srxLeft;
  std::shared_ptr<WPI_TalonSRX> _srxRight;
};
