#include "SubGearPickup.h"
#include "../RobotMap.h"

SubGearPickup::SubGearPickup() : Subsystem("ExampleSubsystem") {
	pnuScoop = RobotMap::subGearPickupPnuScoop;
	tnxSuck = RobotMap::subGearPickupTnxSuck;
}

void SubGearPickup::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void SubGearPickup::Out() {
	pnuScoop->Set(DoubleSolenoid::kForward);
}

void SubGearPickup::In() {
	pnuScoop->Set(DoubleSolenoid::kReverse);
}

void SubGearPickup::Suck(){
	tnxSuck->Set(1);
}

void SubGearPickup::Stop(){
	tnxSuck->Set(0);
}
