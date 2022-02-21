#include "commands/CmdShootSequence.h"
#include "commands/CmdShooter.h"
#include "commands/CmdSpinUpShooter.h"
#include "commands/CmdStorageIn.h"
#include "commands/CmdTrackTarget.h"

#include <frc2/command/InstantCommand.h>
#include <frc2/command/waitCommand.h>

CmdShootSequence::CmdShootSequence(SubStorage* subStorage,
                                   SubShooter* subShooter,
                                   SubIntake* subIntake,
                                   SubDriveBase* subDriveBase) {
  AddCommands(
    //replace with vision shoot
    CmdShooter(subShooter),
    frc2::SequentialCommandGroup(
      frc2::InstantCommand([subStorage] { subStorage->In(); }),
      CmdTrackTarget(subDriveBase, subShooter),
      //replace with vision shoot
      CmdShooter(subShooter),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.5_s),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
      //replace with vision shoot
      CmdShooter(subShooter),
      frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
      frc2::WaitCommand(0.5_s),
      frc2::InstantCommand([subStorage] { subStorage->Stop(); }),
      frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
      frc2::InstantCommand([subShooter] { subShooter->RunAtIdle(); })
    )
  );
}
