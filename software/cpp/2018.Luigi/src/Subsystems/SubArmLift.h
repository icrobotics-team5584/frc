#ifndef SubArmLift_H
#define SubArmLift_H

#include <Commands/Subsystem.h>
#include <ctre/phoenix.h>

class SubArmLift : public Subsystem {
private:

	std::shared_ptr<WPI_TalonSRX> tnxRight;
	std::shared_ptr<WPI_TalonSRX> tnxLeft;
	std::shared_ptr<WPI_TalonSRX> tnxBottom;

public:
	SubArmLift();
	void InitDefaultCommand();
	void Up();
	void Down();
	void Stop();
};

#endif  // SubArmLift_H
