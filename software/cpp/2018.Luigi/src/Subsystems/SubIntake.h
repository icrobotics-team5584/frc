#ifndef SubIntake_H
#define SubIntake_H

#include <Commands/Subsystem.h>
#include <ctre/phoenix.h>

class SubIntake : public Subsystem {
private:
	std::shared_ptr<WPI_TalonSRX> tnxRight;
	std::shared_ptr<WPI_TalonSRX> tnxLeft;
	std::shared_ptr<WPI_TalonSRX> tnxBottom;

public:
	SubIntake();
	void InitDefaultCommand();
	void In();
	void Out();
	void Stop();
};

#endif  // SubIntake_H
