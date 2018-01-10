#include "SubPnuematicOutput.h"

SubPnuematicOutput::SubPnuematicOutput() : Subsystem("SubPnuematicOutput") {
	solPusher.reset(new DoubleSolenoid(0,2));
}

void SubPnuematicOutput::InitDefaultCommand() {
	//SetDefaultCommand(new CmdPnuematicOutputOut());
}

void SubPnuematicOutput::Out() {
	solPusher->Set(DoubleSolenoid::kForward);
}

void SubPnuematicOutput::In() {
	solPusher->Set(DoubleSolenoid::kReverse);
}
