#include "commands/CmdShootSequence.h"
#include "commands/CmdSpinUpShooter.h"
#include "commands/CmdStorageIn.h"

#include <frc2/command/InstantCommand.h>
#include <frc2/command/waitCommand.h>

CmdShootSequence::CmdShootSequence(SubStorage* subStorage,
                                   SubShooter* subShooter,
                                   SubIntake* subIntake) {
  AddCommands(
    CmdSpinUpShooter(subShooter, 2000),
    frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
    frc2::InstantCommand([subStorage] { subStorage->In(); }),
    frc2::WaitCommand(3_s),
    frc2::InstantCommand([subStorage] { subStorage->Stop(); }),
    frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
    frc2::InstantCommand([subShooter] { subShooter->RunAtIdle(); })
  );
}
