#ifndef SubRamp_H
#define SubRamp_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <SmartDashboard/SmartDashboard.h>

class SubRamp : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<VictorSP> SPLeft;
	int _startAutoCount = 0;

	int _scaleCount = 0;
	int _scaleTarget = 70;  //wait for scale to go up

	int _dropCount = 0;
	int _dropTarget = 8; //ramp motor relase time

	int _climbCount = 0;
	int _climbTarget = 30; //wait for ramp drop time


public:
	SubRamp();
	void InitDefaultCommand();
	void DropRamp();
	void AutoDropRamp();
	int GetScaleFinishedCase();
	void StopRamp();
	void AutoStopRamp();
	void ResetRamp();
	void GotoClimbHeight();
	void Periodic();
};

#endif  // SubRamp_H
