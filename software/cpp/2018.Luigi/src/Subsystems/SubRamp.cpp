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

void SubRamp::DropRamp(){ //start spining

	SPLeft->Set(0.4);

}

void SubRamp::ResetRamp() {

	SPLeft->Set(0.2);

}

void SubRamp::StopRamp() {

	SPLeft->Set(0.0);

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
