// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/CmdClimb.h"
#include "Commands/CmdGearPusher.h"
#include "Commands/CmdGearPusherDoor.h"
#include "Commands/CmdJoystickDrive.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    joystick.reset(new Joystick(0));
    
    btnClimber.reset(new JoystickButton(joystick.get(), 3));
    btnClimber->WhileHeld(new CmdClimb());
    btnGearPusherDoor.reset(new JoystickButton(joystick.get(), 2));
    btnGearPusherDoor->WhileHeld(new CmdGearPusherDoor());
    btnGearPusher.reset(new JoystickButton(joystick.get(), 1));
    btnGearPusher->WhileHeld(new CmdGearPusher());

    // SmartDashboard Buttons
    SmartDashboard::PutData("CmdClimb", new CmdClimb());
    SmartDashboard::PutData("CmdJoystickDrive", new CmdJoystickDrive());
    SmartDashboard::PutData("CmdGearPusherDoor", new CmdGearPusherDoor());
    SmartDashboard::PutData("CmdGearPusher", new CmdGearPusher());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getJoystick() {
   return joystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS