#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmUp.h"
#include "Commands/CmdArmDown.h"

OI::OI() {
    //Initiate Joystick
	joystick0.reset(new frc::Joystick(0));

    //Initiate Intake button
    btnIntake.reset(new JoystickButton(joystick0.get(), 2));
    btnIntake->WhileHeld(new CmdIntake());

    //Initiate Output button
    btnOutput.reset(new JoystickButton(joystick0.get(), 1));
	btnOutput->WhileHeld(new CmdOutput());

	//Initiate Arm Up button
	btnArmUp.reset(new JoystickButton(joystick0.get(), 5));
	btnArmUp->WhileHeld(new CmdArmUp());

	//Initiate Arm Down button
	btnArmDown.reset(new JoystickButton(joystick0.get(), 3));
	btnArmDown->WhileHeld(new CmdArmDown());

}


std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;
}
