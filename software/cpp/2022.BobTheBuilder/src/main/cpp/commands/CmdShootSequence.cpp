#include "commands/CmdShootSequence.h"
#include "commands/CmdShooter.h"
#include "commands/CmdSpinUpShooter.h"
#include "commands/CmdStorageIn.h"
#include "commands/CmdTrackTarget.h"
#include "commands/CmdVisionShoot.h"
#include <frc2/command/InstantCommand.h>
#include <frc2/command/waitCommand.h>
#include <frc2/command/WaitUntilCommand.h>

CmdShootSequence::CmdShootSequence(SubStorage* subStorage,
                                   SubShooter* subShooter,
                                   SubIntake* subIntake,
                                   SubDriveBase* subDriveBase) {
  AddCommands(
    //replace with vision shoot
    frc2::InstantCommand([subShooter] { subShooter->SetShooterTracking(true); }),
    frc2::InstantCommand([subIntake] {subIntake->Extend(); }),
    frc2::InstantCommand([subStorage] { subStorage->In(); }),
    CmdTrackTarget(subDriveBase, subShooter),
    frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
    frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
    frc2::WaitCommand(0.5_s),
    frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
    frc2::WaitUntilCommand([subShooter] { return subShooter->IsAtTargetSpeed(); }),
    frc2::InstantCommand([subStorage] { subStorage->RetractStopper(); }),
    frc2::WaitCommand(0.5_s),
    
    frc2::InstantCommand([subStorage] { subStorage->Stop(); }),
    frc2::InstantCommand([subStorage] { subStorage->ExtendStopper(); }),
    frc2::InstantCommand([subIntake] {subIntake->Retract(); })
  );
}
