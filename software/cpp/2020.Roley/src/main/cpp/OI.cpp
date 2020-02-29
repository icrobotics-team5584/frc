/*----------------------------------------------------------------------------*/
/* OI.cpp                                                                     */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>

#include "OI.h"
#include "commands/CmdShooterShoot.h"
#include "commands/CmdRollStorage.h"
#include "commands/CmdRollStorageBack.h"
#include "commands/CmdDriveSlowDown.h"
#include "commands/CmdIntake.h"
#include "commands/CmdDeployIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdClimberLimitUp.h"
#include "commands/CmdDeployDolly.h"
#include "commands/CmdBuddyDeploy.h"
#include "commands/CmdBuddyLock.h"
#include "commands/CmdEngageClimberRatchets.h"
#include "commands/CmdStorageExpand.h"
#include "commands/CmdStorageRetract.h"
#include "commands/CmdStorageTogglePneumatic.h"
#include "commands/CmdElevatorFullExtend.h"
#include "commands/CmdElevaterExtendMin.h"
#include "commands/CmdElevatorBuddy.h"
#include "commands/CmdShootSequence.h"
#include "commands/CmdIntakeOutTake.h"

OI::OI() {

  //std::cout<< "OI Started" << std::endl;

  //Setup Joystick (0)
  joystick1.reset(new frc::Joystick(0));

  btnShoot.reset(new frc::JoystickButton(joystick1.get(), aBtn));
  btnShoot->WhileHeld(new CmdShootSequence());

  //Slow drive buttons
  btnSlowDown.reset(new AxisButton(joystick1.get(), triggerL));
  btnSlowDown->WhileHeld(new CmdDriveSlowDown());

  //Intake buttons
  btnDeployIntake.reset(new frc::JoystickButton(joystick1.get(), rightBtn));
  btnIntake.reset(new frc::JoystickButton(joystick1.get(), leftBtn));
  //btnOuttake.reset(new frc::JoystickButton(joystick1.get(), rightBtn));
  btnDeployIntake->WhileHeld(new CmdDeployIntake());
  btnIntake->WhileHeld(new CmdIntake());
  //btnOuttake->WhileHeld(new CmdOuttake());

  //Intake reverse

  btnIntakeReverse.reset(new frc::JoystickButton(joystick1.get(), yBtn));
  btnIntakeReverse->WhileHeld(new CmdIntakeOutTake());


  //Climber Button

  //btnClimb.reset(new frc::JoystickButton(joystick1.get(), leftStickBtn));
  //btnClimb->WhileHeld(new CmdClimberLimitUp());
  //btnRatchets.reset(new frc::JoystickButton(joystick1.get(), aBtn));
  //btnRatchets->WhileHeld(new CmdEngageClimberRatchets());

  //Storage Pneumatics
  btnReverseStorage.reset(new frc::JoystickButton(joystick1.get(), bBtn));
  btnReverseStorage->WhileHeld(new CmdRollStorageBack());

  //std::cout<< "OI Ended" << std::endl;

  //Buddy Climber Button

  btnReleaseBuddyClimber.reset(new frc::JoystickButton(joystick1.get(), backBtn));
  btnReleaseBuddyClimber->WhenPressed(new CmdBuddyLock());

  btnOverride.reset(new frc::JoystickButton(joystick1.get(), startBtn));
  // btnOverride->WhileHeld(new )

  btnElevaterDown.reset(new ButtonPOV(joystick1.get(), DOWN));
  btnElevaterDown->WhenPressed(new CmdElevaterExtendMin());

  btnElevaterUp.reset(new ButtonPOV(joystick1.get(), UP));
  btnElevaterUp->WhenPressed(new CmdElevatorFullExtend());

  btnElevaterBuddy.reset(new ButtonPOV(joystick1.get(), RIGHT));
  btnElevaterBuddy->WhenPressed(new CmdElevatorBuddy());

}

bool OI::GetOverride(){
  return btnOverride->Get();
}


double OI::getJoystickX(){
  return joystick1->GetX();
}

double OI::getJoystickY(){
  return joystick1->GetY();
}

double OI::getJoystick2X(){
  return joystick1->GetRawAxis(4);
}

double OI::getJoystick2Y(){
  return joystick1->GetRawAxis(5);
}

double OI::getJoystickRawAxis(Triggers trigger){
  return joystick1->GetRawAxis(trigger);
}

double OI::GetRightAsix(){
  return btnSlowDown->GetAxis();
}