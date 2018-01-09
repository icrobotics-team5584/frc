#include "SubPnuematicOutput.h"
#include "../RobotMap.h"

SubPnuematicOutput::SubPnuematicOutput() : Subsystem("ExampleSubsystem") {
	//std::shared_ptr<DoubleSolenoid> SubPnuematicOutput::solPusher;
	subPnuematicOutputSolPusher.reset(new DoubleSolenoid(0,2));
}

void SubPnuematicOutput::InitDefaultCommand() {
	//SetDefaultCommand(new CmdPnuematicOutputOut());
}

void SubPnuematicOutput::Out() {
	subPnuematicOutputSolPusher->Set(DoubleSolenoid::kForward);
}

void SubPnuematicOutput::In() {
	subPnuematicOutputSolPusher->Set(DoubleSolenoid::kReverse);
}
