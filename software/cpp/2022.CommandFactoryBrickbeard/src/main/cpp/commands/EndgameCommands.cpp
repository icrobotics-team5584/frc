#include "commands/EndgameCommands.h"

#include "subsystems/SubClimber.h"

namespace cmd {
using namespace frc2::cmd;

/*
 * Start the climb sequence by resetting the climber to its bottom position, then calling the 
 * climb sequence as a proxy after the X button is pressed. Climb sequence is called as a proxy
 * from here rather than just putting all of this inside the climb sequence so that if 
 * StartClimbSequence is restarted while the climb sequence is already running, it can interrupt
 * the currently running climb sequence and start a new one.
 * If this was all part of the ClimbSequence, you wouldn't be able to restart it just by running
 * it again because a command cannot interrupt itself.
 * Requires: SubElevator (inherited from ElevateTo)
 */
frc2::CommandPtr StartClimbSequence(frc2::CommandXboxController& controller){
    return StowClimbers()
        .AndThen(ElevateTo(SubClimber::MIN_HEIGHT))
        .AndThen(WaitForXButton(controller))
        .AndThen(ClimbSequence(controller).AsProxy());
}

/*
 * The climb sequence. Wait for the driver to press the X button between steps.
 * Requires: SubElevator (inherited from ElevateTo)
 */
frc2::CommandPtr ClimbSequence(frc2::CommandXboxController& controller) {
  return Sequence(
      // extend to mid bar
      ElevateTo(SubClimber::NEAR_MAX_HEIGHT),
      WaitForXButton(controller),

      // pull up to mid bar
      ElevateTo(SubClimber::MIN_HEIGHT),
      ElevateTo(SubClimber::NEAR_MIN_HEIGHT),
      WaitForXButton(controller),

      // rotate and extend arms toward high bar
      RotateClimbers(),
      Wait(1_s),
      ElevateTo(SubClimber::MAX_HEIGHT),
      StowClimbers(),
      WaitForXButton(controller),

      // pull up to high bar
      ElevateTo(SubClimber::MIN_HEIGHT),
      ElevateTo(SubClimber::NEAR_MIN_HEIGHT),
      WaitForXButton(controller),

      // rotate and extend arms toward traversal bar
      RotateClimbers(),
      Wait(1_s),
      ElevateTo(SubClimber::MAX_HEIGHT),
      StowClimbers(),
      WaitForXButton(controller),

      // pull up to traversal bar
      ElevateTo(SubClimber::MIN_HEIGHT),
      ElevateTo(SubClimber::NEAR_MIN_HEIGHT)
  );
}

/*
 * Do nothing until the X button is pressed on the supplied xbox controller.
 */
frc2::CommandPtr WaitForXButton(frc2::CommandXboxController& controller) {
  return WaitUntil([&] { return controller.GetXButton(); });
}

/*
 * Elevate the climber arms to a height in meters. Continues running until the height is reached.
 */
frc2::CommandPtr ElevateTo(units::meter_t height){
  // Run once at the beginning so the target height can be set before the end condition 
  // (IsAtTargetHeight) is checked.
  // Then run continuously after that so if we hit an end stop it doesn't just stop moving.
  return 
    RunOnce([height] { SubClimber::GetInstance().DriveTo(height); })
    .AndThen(
      Run([height] { SubClimber::GetInstance().DriveTo(height); }, {&SubClimber::GetInstance()})
      .Until([] { return SubClimber::GetInstance().IsAtTargetPosition(); })
    );
}

/*
 * Rotate the climbers outward toward the next bar.
 */
frc2::CommandPtr RotateClimbers() {
  return RunOnce([] { SubClimber::GetInstance().Rotate(); });
}

/*
 * Rotate the climbers inward to pull bot onto the currently hooked bar. 
 */
frc2::CommandPtr StowClimbers() {
  return RunOnce([] { SubClimber::GetInstance().Stow(); });
}

/*
 * Move climber arms at a percentage power.
 */
frc2::CommandPtr ManualClimb(double speed){
  return StartEnd([speed] { SubClimber::GetInstance().ManualDrive(speed); },
                  [] { SubClimber::GetInstance().ManualDrive(0); });
}

/*
 * Toggle between stowed and rotated climber arm positions. While this command is running, arms
 * are in the rotated out position.
 */
frc2::CommandPtr ToggleRotateClimbers() {
  return StartEnd([] { SubClimber::GetInstance().Rotate(); },
                  [] { SubClimber::GetInstance().Stow(); });
}

}  // namespace cmd
