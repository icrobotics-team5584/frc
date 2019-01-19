/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <pathfinder-frc.h>

class CmdFollowPath : public frc::Command {
 public:
  CmdFollowPath();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:
    int length;

    Segment * seg;
    Segment * leftTrajectory;
    Segment * rightTrajectory;

    EncoderConfig leftConfig;
    EncoderConfig rightConfig;

    EncoderFollower * leftFollower;
    EncoderFollower * rightFollower;
};
