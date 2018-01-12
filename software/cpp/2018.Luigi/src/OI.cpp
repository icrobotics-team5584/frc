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
    btnOutput.reset(new JoystickButton(joystick0.get(), 1));
	btnOutput->WhileHeld(new CmdIntake());
}


std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;
}
