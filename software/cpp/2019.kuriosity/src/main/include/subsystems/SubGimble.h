#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include "subsystems/PIDPot.h"

using namespace std;
using namespace frc;

class SubGimble : public frc::Subsystem {
 private:
  
  shared_ptr<WPI_TalonSRX> _srxGimble; 
  shared_ptr<AnalogInput> _anaGimblePot;
  PIDController* gimbleController;
  PIDPot* _potSourcePID;

  double rotateSpeed = 0.5; //Max rotating power
  double PotLeft = 2538;
	double PotRight = 512;
	double PotCentre = 1612;
	double PIDp = 0.0035;
	double PIDi = 0.00002;
	double PIDd = 0.007;
  double humanOffset = 10.0;  //Used for overide 
  double overrideTarget = 0.0;
  int potRange = 0;
  int target = 0;
	int lc = 0;
  int totalAngle = 180;


  public:
  SubGimble();
  void Periodic();
  void InitDefaultCommand() override;
  void rotateLeft();
  void rotateRight();
  void stop();
  //void Reset();  Maybe in the future this can reset the left and right values?
  void enable();
  void disable();
  void PIDGimbleTo(int angle);  
  void OverridePID(bool leftRight);
};
