#include "OI.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosSwitch.h"
#include "Commands/CmdAutoMotionProfileTest.h"
#include "Commands/CmdChangeCamera.h"


OI::OI() {
    //Initiate Joystick
	joystick0.reset(new frc::Joystick(0));

    //Initiate Intake button
	btnIntake.reset(new JoystickButton(joystick0.get(), 2));
	btnIntake->WhileHeld(new CmdOutput());

    //Initiate Output button
    btnOutput.reset(new JoystickButton(joystick0.get(), 1));
	btnOutput->WhileHeld(new CmdOutput());

	//Initiate Arm Encoded Actuator controls
	btnArmToGround.reset(new JoystickButton(joystick0.get(), 1));
	btnArmToGround->WhenPressed(new CmdArmPosGround());
	btnArmToSwitch.reset(new JoystickButton(joystick0.get(), 3));
	btnArmToSwitch->WhenPressed(new CmdArmPosSwitch());
	btnArmToScale.reset(new JoystickButton(joystick0.get(), 4));
	btnArmToScale->WhenPressed(new CmdArmPosScale());

	//Motion Profile test
	btnMP.reset(new JoystickButton(joystick0.get(), 44));
	// btnMP->ToggleWhenPressed(new CmdAutoMotionProfileTest());
	btnMP->WhileHeld(new CmdAutoMotionProfileTest());

	//Initiate Change camera button
	btnChangeCamera.reset(new JoystickButton(joystick0.get(), 99));
	btnChangeCamera->WhenPressed(new CmdChangeCamera());

}


std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;
}
