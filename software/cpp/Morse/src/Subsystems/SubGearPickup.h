#ifndef SubGearPickup_H
#define SubGearPickup_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "CANTalon.h"

class SubGearPickup : public Subsystem {
private:
	std::shared_ptr<DoubleSolenoid> pnuScoop;
	std::shared_ptr<CANTalon> tnxSuck;

public:
	SubGearPickup();
	void InitDefaultCommand();
	void In();
	void Out();
	void Suck();
	void Stop();
};

#endif  // SubGearPickup_H
