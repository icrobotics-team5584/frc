#pragma once

#include <frc/commands/Command.h>

class SafteyController {
 friend class SafteyCommand; // Let SafteyCommands use SafteyContollers' private members

 public:
  SafteyController();

 private:
  enum class Direction {FORWARD, BACKWARD, IDLE};
  SafteyCommand safteyCommand;
  int prevEncoderValue = 0;
  Direction GetEncoderDirection();
  Direction GetMotorDirection();
  void Periodic();

 protected:
  virtual int GetEncoderValue() = 0;
  virtual double GetMotorPower() = 0;
};

// This command is purely a mechanism to periodically update the SafteyController, like a timed
// loop. This could be replaced with a frc2::RunCommand when we move to the new (2020) command
// based structure.
class SafteyCommand : public frc::Command {
  public:
    SafteyCommand(SafteyController* controller) {this->controller = controller;};
    void Execute() override {controller->Periodic();};
    bool IsFinished() override {return false;};
  private:
    SafteyController* controller;
};