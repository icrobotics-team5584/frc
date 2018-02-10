#include "SubRamp.h"
#include "../RobotMap.h"
#include "Commands/CmdRampDefault.h"

//std::unique_ptr<CmdRampDrop> SubRamp::cmdRampDrop;

SubRamp::SubRamp() : Subsystem("ExampleSubsystem") {

	SPLeft = RobotMap::subRampSPLeft;

}

void SubRamp::InitDefaultCommand() {
	SetDefaultCommand(new CmdRampDefault());
}



// Put methods for controlling this subsystem
// here. Call these from Commands.
