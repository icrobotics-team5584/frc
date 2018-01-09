#ifndef SubDriveTrain_H
#define SubDriveTrain_H

#include <Commands/Subsystem.h>

class SubDriveTrain : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	SubDriveTrain();
	void InitDefaultCommand();
};

#endif  // SubDriveTrain_H
