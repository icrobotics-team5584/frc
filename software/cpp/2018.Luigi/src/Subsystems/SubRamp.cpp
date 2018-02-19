#include "SubRamp.h"
#include "../RobotMap.h"
#include "Commands/CmdRampDefault.h"
#include "Commands/CmdArmPosScale.h"
#include "Commands/CmdArmPosClimb.h"

//std::unique_ptr<CmdRampDrop> SubRamp::cmdRampDrop;

SubRamp::SubRamp() : Subsystem("ExampleSubsystem") {

	SPLeft = RobotMap::subRampSPLeft;

}

void SubRamp::InitDefaultCommand() {
	SetDefaultCommand(new CmdRampDefault());
}

void SubRamp::DropRamp(){ //start spining

	SPLeft->Set(0.4);
	_startAutoCount = 2;

}

//		CmdPrepForClimb *cmdPrepForClimbPtr;
//		cmdPrepForClimbPtr = new CmdPrepForClimb;
//		cmdPrepForClimbPtr->Start();

void SubRamp::AutoDropRamp() {

		CmdArmPosScale * cmdArmPosScalePtr;
		cmdArmPosScalePtr  = new CmdArmPosScale;
		cmdArmPosScalePtr->Start();

		_startAutoCount = 1;

}


void SubRamp::Periodic() {

	switch (_startAutoCount) {
	case 0 :
	break;
	case 1 :
		if (_scaleCount >= _scaleTarget) { //wait for scale
			DropRamp();
		} else {
			_scaleCount++;
		}
	break;
	case 2 :
		if (_dropCount >= _dropTarget) { //Stop the motor,, ramp rel
			AutoStopRamp(); //stop motor ramp rel
		} else {
			_dropCount++;
		}
	break;
	case 3 :
		if (_climbCount >= _climbTarget) { //wait for ramp drop time
			GotoClimbHeight();
		} else {
			_climbCount++;
		}
	break;
	}

}

void SubRamp::ResetRamp() {

	SPLeft->Set(-0.2);
	_startAutoCount = 0;
}

void SubRamp::StopRamp() {

	SPLeft->Set(0.0);

}

void SubRamp::AutoStopRamp() {

	SPLeft->Set(0.0);

	_startAutoCount = 3;

}

void SubRamp::GotoClimbHeight() {

	CmdArmPosClimb * cmdArmPosClimbPtr;
	cmdArmPosClimbPtr  = new CmdArmPosClimb;
	cmdArmPosClimbPtr->Start();

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
