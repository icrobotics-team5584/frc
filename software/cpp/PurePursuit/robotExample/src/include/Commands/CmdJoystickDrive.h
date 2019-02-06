#pragma once

#include <Commands/Command.h>
#include <WPILib.h>

using namespace std;

class CmdJoystickDrive : public frc::Command {
public:
  CmdJoystickDrive();
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;

private:
  shared_ptr<Joystick> m_controller;

};
