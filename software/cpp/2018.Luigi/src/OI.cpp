#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdIntake.h"

OI::OI() {
    //Initiate Joystick
	joystick0.reset(new frc::Joystick(0));

    //Initiate Intake button
    btnIntake.reset(new JoystickButton(joystick0.get(), 1));
    btnIntake->WhileHeld(new CmdIntake());

    //Initiate Output button
    btnOutput.reset(new JoystickButton(joystick0.get(), 2));
	btnOutput->WhileHeld(new CmdIntake());

	//Initiate Arm Up button
	btnArmUp.reset(new JoystickButton(joystick0.get(), 3));
	btnArmUp->WhileHeld(new CmdIntake());
	//Initiate Arm Down button
	btnArmDown.reset(new JoystickButton(joystick0.get(), 4));
	btnArmDown->WhileHeld(new CmdIntake());


}


std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;
}
