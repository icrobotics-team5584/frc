#include "SubRamp.h"
#include "../RobotMap.h"
#include "Commands/CmdRampDrop.h"

SubRamp::SubRamp() : Subsystem("ExampleSubsystem") {

	SPLeft = RobotMap::subRampSPLeft;

}

void SubRamp::InitDefaultCommand() {
	SetDefaultCommand(new CmdRampDrop());
}

void SubRamp::TakeJoystickInputs(std::shared_ptr<Joystick> sticky_3) {

	_POV = sticky_3->GetPOV();

	frc::SmartDashboard::PutNumber("POV  ========", _POV);

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
