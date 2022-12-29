#include "commands/BallCommands.h"
#include "commands/DriveCommands.h"
#include "subsystems/SubDrivebase.h"
#include "subsystems/SubIntake.h"
#include "subsystems/SubShooter.h"
#include "subsystems/SubStorage.h"
#include "utilities/Vision.h"
#include <units/time.h>
#include <frc2/command/ScheduleCommand.h>
#include <frc2/command/CommandScheduler.h>
#include <memory>


namespace cmd {
using namespace frc2::cmd;

/* 
 * On start: deploy intake, start spinning intake roller, start running storage conveyor inward
 * On end: retract intake, stop spinning intake roller, stop storage conveyor after 2 seconds
 * Requires: SubStorage and SubIntake
 */
frc2::CommandPtr Intake() {
  return StartEnd(
    [] {
      SubIntake::GetInstance().Deploy();
      SubIntake::GetInstance().Intake();
      SubStorage::GetInstance().Start();
    }, 
    [] {
      SubIntake::GetInstance().Stop();
      SubIntake::GetInstance().Retract();
      auto static waitThenStop = Wait(2_s).AndThen([]{SubStorage::GetInstance().Stop();});
      waitThenStop.Schedule();
    },
    {&SubStorage::GetInstance(), &SubIntake::GetInstance()}
  );
}

/* 
 * Accelerate the shooter flywheel to the correct speed to fire a ball into the goal from the
 * distance computed by the vision system. Run this on a loop forever until interrupted.
 * Requires: SubShooter
 */
frc2::CommandPtr AccelerateFlyweelToTarget() {
  return Run(
    [] {
      auto dist = FakeVision::GetDistToTarget();
      SubShooter::GetInstance().AccelerateFlywheel(dist);
    }, 
    {&SubShooter::GetInstance()}
  );
}

/* 
 * While accelerating the flywheel to speed, start the storage conveyor running inward (feeding
 * balls to the shooter), then release a ball into the flywheel once it is up to speed.
 * Wait 0.5 sec for the ball to pass through before blocking the storage again with the blocker
 * pistons. The cleanup (resetting the storage by blocking and stopping) happens in a FinallyDo
 * rather than at the end of the sequence so they will still run if the command gets interrupted.
 * Requires: SubShooter (inherited from AccelerateToFlywheel)
 */
frc2::CommandPtr Shoot() {
  return 
  AccelerateFlyweelToTarget()
  .RaceWith( // RaceWith means the whole Shoot command will end once AccelerateToTarget or the Squence ends
    Sequence(
      RunOnce([]{SubStorage::GetInstance().Start();}),
      WaitUntil([]{return SubShooter::GetInstance().AtTargetVelocity();}),
      RunOnce([]{SubStorage::GetInstance().ReleaseBall();}),
      Wait(0.5_s)
    )
  )
  .FinallyDo([](bool _){
    SubStorage::GetInstance().BlockBall();
    SubStorage::GetInstance().Stop();
  });
}

/*
 * Aim the drivebase toward the target and run the storage conveyor inward. Once within 1 degree
 * of the target, shoot twice. Stop the storage inside a FinallyDo rather than at the end of the 
 * sequence so it will still run if the command gets interrupted.
 * Requires: SubDrivebase (inherited from AimAtTarget), SubShooter (inherited from Shoot)
 */
frc2::CommandPtr AimAndShootTwice() {
  return 
  AimAtTarget()
  .RaceWith( // RaceWith means the whole AimAndShootTwice command will end once AimAtTarget or the Squence ends
    Sequence(
      RunOnce([]{SubStorage::GetInstance().Start();}),
      WaitUntil([]{return units::math::abs(FakeVision::GetAngleToTarget()) < 1_deg;}),
      Shoot(),
      Shoot()
    )
  )
  .FinallyDo([](bool _){SubStorage::GetInstance().Stop();});
}

}  // namespace cmd