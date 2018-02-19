#include "OI.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdIntake.h"
#include "Commands/CmdOutput.h"
#include "Commands/CmdArmPosGround.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosSwitch.h"

#include "Commands/CmdArmPosExchange.h"
#include "Commands/CmdArmOveride.h"
#include "Commands/CmdResetArmEncoPos.h"
#include "Commands/CmdChangeCamera.h"

#include "Commands/CmdGyroDrive.h"

OI::OI() {
    //Initiate Joystick
	joystick0.reset(new frc::Joystick(0));

    //Initiate Intake button
	btnIntake.reset(new JoystickButton(joystick0.get(), 6));
	btnIntake->WhileHeld(new CmdIntake());

    //Initiate Output button
    btnOutput.reset(new JoystickButton(joystick0.get(), 5));
	btnOutput->WhileHeld(new CmdOutput());

	//Initiate Arm Encoded Actuator controls
	btnArmToGround.reset(new JoystickButton(joystick0.get(), 1));
	btnArmToGround->WhenPressed(new CmdArmPosGround());
	btnArmToExchange.reset(new JoystickButton(joystick0.get(), 2));
	btnArmToExchange->WhenPressed(new CmdArmPosExchange());
	btnArmToSwitch.reset(new JoystickButton(joystick0.get(), 3));
	btnArmToSwitch->WhenPressed(new CmdArmPosSwitch());
	btnArmToScale.reset(new JoystickButton(joystick0.get(), 4));
	btnArmToScale->WhenPressed(new CmdArmPosScale());
	//Initiate Arm Extras
	btnArmOveride.reset(new JoystickButton(joystick0.get(), 10));
	btnArmOveride->WhileHeld(new CmdArmOveride());
	btnEncoderPosReset.reset(new JoystickButton(joystick0.get(), 8));
	btnEncoderPosReset->WhenPressed(new CmdResetArmEncoPos());

	//Initiate Change camera button
//	btnChangeCamera.reset(new JoystickButton(joystick0.get(), 99));
//	btnChangeCamera->WhenPressed(new CmdChangeCamera());

	//Tempoary Shuffleboard control of autonomous gyro driving
	SmartDashboard::PutData("Drive 5.3", new CmdGyroDrive(5.3,0,false,false));
	SmartDashboard::PutData("Turn to -90", new CmdGyroDrive(0,-90,false,true));
	SmartDashboard::PutData("Drive 4.1", new CmdGyroDrive(4.1, -90, false, false));
	SmartDashboard::PutData("Turn to 0", new CmdGyroDrive(0, 0, false, true));
}


std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;

}
