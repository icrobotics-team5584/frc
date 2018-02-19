#ifndef SubIntake_H
#define SubIntake_H

#include <Commands/Subsystem.h>
#include <ctre/phoenix.h>
#include <WPILib.h>
#include <iostream>

class SubIntake : public Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> tnxRight;
	std::shared_ptr<WPI_TalonSRX> tnxLeft;
	std::shared_ptr<VictorSP> spFinger;
	std::shared_ptr<DigitalInput> swtFingerLimit;
	std::shared_ptr<DigitalInput> swtLeftLimit;
	std::shared_ptr<DigitalInput> swtRightLimit;
	bool fingerDesiredPositionUp;
	int fingerTicks;
	int fingerTicksToMove = 10;

public:
	SubIntake();
	void InitDefaultCommand();
	void Periodic();
	void In(double speed);
	void Out(double speed);
	void Stop();
	bool GetSwitches();
};

#endif  // SubIntake_H
