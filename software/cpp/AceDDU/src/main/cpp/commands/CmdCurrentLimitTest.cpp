/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdCurrentLimitTest.h"
#include <Robot.h>

/* Hi, here's a little info about this class.
*  The intake on the new DDU bot (if it works) will require current limiting, since the intake is using a 775pro and will 100% stall no matter what you do (or just don't intake hatches)
*  775pro's are known to burn out in like...2s...not very good for us, right?
*  As well as an ONBOARD CAN PID CONTROLLER *cough* Liam *cough*, the talon has many other cool things it can do. This includes current limiting (wooooo)
*  When a motor gets stalled, it draws more current than it would when spinning freely. This causes the motor to heat up, which leads to the brushes melting off and commutator falling out
*  and all that (as we saw on Dizzy's lift), which is BAD, because we don't want to waste our resources. So how does current limiting help us? So lets theoreticaly say the driver operating
*  the robot does not have superhuman skills that can see when the motor is stalling and will stop the motors. Current limiting will bring the current to 'x' when it sees that it is exceeding
*  what it should be, so that the motors don't burn out.
*  
*  The command I have written is simply a test for current limiting, and won't be used for the final robot. We should be able to do this before we start programming mechanisms, so we know
*  exactly what to do when the time comes.
*
*  I recommend you to have a quick read through the class, see what it does, how it works, and then try to test it the next time you get the chance.
*/
CmdCurrentLimitTest::CmdCurrentLimitTest() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(Robot::subDrivebase.get());
}

// Called just before this Command runs the first time
void CmdCurrentLimitTest::Initialize() {
  Robot::subDrivebase->srxFrontLeft->ConfigPeakCurrentLimit(30); //don't activate current limit until current exceeds 30 A ...
  Robot::subDrivebase->srxFrontLeft->ConfigPeakCurrentDuration(100); // ... for at least 100 ms
  Robot::subDrivebase->srxFrontLeft->ConfigContinuousCurrentLimit(20); // once current-limiting is actived, hold at 20A
  Robot::subDrivebase->srxFrontLeft->EnableCurrentLimit(true);
}

// Called repeatedly when this Command is scheduled to run
void CmdCurrentLimitTest::Execute() {
  //try to stop it from moving and see what happens
  //ALSO ONLY TRY THIS ON CIMS. DO NOT ATTEMPT TO TEST ON A 775PRO.
  Robot::subDrivebase->srxFrontLeft->Set(0.5);
  talonCurrentDraw = Robot::subDrivebase->srxFrontLeft->GetOutputCurrent();
  frc::SmartDashboard::PutNumber("Front Left SRX Current Draw", talonCurrentDraw);

}

// Make this return true when this Command no longer needs to run execute()
bool CmdCurrentLimitTest::IsFinished() { return false; }

// Called once after isFinished returns true
void CmdCurrentLimitTest::End() {
  Robot::subDrivebase->srxFrontLeft->EnableCurrentLimit(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CmdCurrentLimitTest::Interrupted() {}
