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
#include "commands/CmdOuttake.h"
#include "commands/CmdClimberLimitUp.h"
#include "commands/CmdDeployDolly.h"
#include "commands/CmdBuddyDeploy.h"
#include "commands/CmdBuddyLock.h"
#include "commands/CmdStorageExpand.h"
#include "commands/CmdStorageRetract.h"
#include "commands/CmdStorageTogglePneumatic.h"

OI::OI() {

  //std::cout<< "OI Started" << std::endl;

  //Setup Joystick (0)
  joystick1.reset(new frc::Joystick(0));
  
  btnShoot.reset(new frc::JoystickButton(joystick1.get(), bBtn));
  btnShoot->WhileHeld(new CmdShooterShoot());

  //Storage buttons
  btnForward.reset(new frc::JoystickButton(joystick1.get(),xBtn));
  btnBackward.reset(new frc::JoystickButton(joystick1.get(),yBtn));
  btnForward->WhileHeld(new CmdRollStorage());
  btnBackward->WhileHeld(new CmdRollStorageBack());

  //Slow drive buttons
  btnSlowDown.reset(new AxisButton(joystick1.get(), triggerL));
  btnSlowDown->WhileHeld(new CmdDriveSlowDown());

  //Intake buttons
  btnIntake.reset(new frc::JoystickButton(joystick1.get(), leftBtn));
  btnOuttake.reset(new frc::JoystickButton(joystick1.get(), rightBtn));
  btnIntake->WhileHeld(new CmdIntake());
  btnOuttake->WhileHeld(new CmdOuttake());

  //Climber Button

  btnClimb.reset(new frc::JoystickButton(joystick1.get(), leftStickBtn));
  btnClimb->WhileHeld(new CmdClimberLimitUp());

  //Storage Pneumatics
  btnStorageExpand.reset(new frc::JoystickButton(joystick1.get(),aBtn));
  btnStorageExpand->ToggleWhenPressed(new CmdStorageTogglePneumatic);

  //std::cout<< "OI Ended" << std::endl;

  //Buddy Climber Button

  btnReleaseBuddyClimber.reset(new frc::JoystickButton(joystick1.get(), backBtn));
  btnReleaseBuddyClimber->WhileHeld(new CmdBuddyLock());

  btnOverride.reset(new frc::JoystickButton(joystick1.get(), startBtn));
  // btnOverride->WhileHeld(new )

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

double OI::getJoystickRawAxis(Triggers trigger){
  return joystick1->GetRawAxis(trigger);
}

double OI::GetRightAsix(){
  return btnSlowDown->GetAxis();
}