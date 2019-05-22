/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/buttons/ButtonScheduler.h"

namespace frc {

class Trigger;
class Command;

class SwitchButtonSceduler : public ButtonScheduler {
 public:
  SwitchButtonSceduler(bool last, Trigger* button, Command* orders1, Command* orders2);
 private:
  Command* secondaryCommand;
  void Execute();
};

} //namespace