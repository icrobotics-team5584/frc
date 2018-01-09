#include "SubPnuematicOutput.h"
#include "../RobotMap.h"

SubPnuematicOutput::SubPnuematicOutput() : Subsystem("ExampleSubsystem") {

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
