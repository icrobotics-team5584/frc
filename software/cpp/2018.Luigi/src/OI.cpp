#include "OI.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/MyJoystickDrive.h"
#include "Commands/CmdIntake.h"

OI::OI() {
    joystick0.reset(new frc::Joystick(0));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("MyJoystickDrive", new MyJoystickDrive());
    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    btnIntake.reset(new JoystickButton(joystick0.get(), 1));
    btnIntake->WhileHeld(new CmdIntake());
}


std::shared_ptr<frc::Joystick> OI::getJoystick0() {
   return joystick0;
}
