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
  double PotLeft = 778;
	double PotRight = 3446;
	double PotCentre = 2112;
	double PIDp = -0.0025;
	double PIDi = 0.0001;
	double PIDd = -0.0015;
  double humanOffset = 0.001;  //Used for overide 
  double overrideSpeed = 0.0;
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
  void PIDGimbleTo(double angle);  
  void OverridePID(bool leftRight);
};
