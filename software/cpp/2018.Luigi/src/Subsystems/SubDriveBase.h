#ifndef SubDriveBase_H
#define SubDriveBase_H

#include <Commands/Subsystem.h>

class SubDriveBase : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	SubDriveBase();
	void InitDefaultCommand();
};

#endif  // SubDriveBase_H
