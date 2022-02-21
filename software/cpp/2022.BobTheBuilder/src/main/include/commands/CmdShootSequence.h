#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/SubIntake.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubStorage.h"

class CmdShootSequence
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 CmdShootSequence> {
 public:
  CmdShootSequence(SubStorage* subStorage, SubShooter* subShooter,
                   SubIntake* subIntake);
};
