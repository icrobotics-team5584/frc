#pragma once

#include <frc/WPILib.h>
#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include "subsystems/PIDPot.h"
#include "subsystems/gimblePID.h"

using namespace std;
using namespace frc;

class SubGimble : public frc::Subsystem {
 private:
  
  shared_ptr<WPI_TalonSRX> _srxGimble; 
  shared_ptr<AnalogInput> _anaGimblePot;
  PIDController* gimbleController;
  PIDPot* _potSourcePID;
  gimblePID* _gimblePID;

  double rotateSpeed = 0.65; //Max rotating power
  double PotLeft = 783;
	double PotRight = 3305;
	double PotCentre = 1905;
	double PIDp = -0.0025;
	double PIDi = 0;
	double PIDd = 0;
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
  void VoltageControl(double percentage);
  void stop();
  //void Reset();  Maybe in the future this can reset the left and right values?
  void enable();
  void disable();
  void PIDGimbleTo(double angle);  
  void OverridePID(bool leftRight);
  void ToCentre();
};
