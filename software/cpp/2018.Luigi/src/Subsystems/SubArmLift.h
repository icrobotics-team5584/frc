#ifndef SubArmLift_H
#define SubArmLift_H

#include <Commands/Subsystem.h>
#include <ctre/phoenix.h>
#include <WPILib.h>



class SubArmLift : public Subsystem {
private:

	std::shared_ptr<WPI_TalonSRX> tnxRight;
	std::shared_ptr<WPI_TalonSRX> tnxLeft;
	std::shared_ptr<WPI_TalonSRX> tnxBottom;

	std::shared_ptr<DigitalInput> swtTopLimit;
	std::shared_ptr<DigitalInput> swtBottomLimit;

public:
	SubArmLift();
	void InitDefaultCommand();
	void Up();
	void Down();
	void Stop();
	bool GetTopSwitch();
	bool GetBottomSwitch();
};

#endif  // SubArmLift_H
