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
  double PotLeft = 784;
	double PotRight = 3339;
	double PotCentre = 1905;
	double PIDp = 0.0025;
	double PIDi = 0;
	double PIDd = 0.0;
  double humanOffset = 0.0;  //Used for overide 
  double overrideSpeed = 50;
  double target = PotCentre;
  int potRange = 0;
	int lc = 0;
  int totalAngle = 180;
  //PID 
  double kP;
  double kI;
  double kD;
  double error;
  double intergral;
  double derivative;
  double lastError = 0;
  double PIDOutput;
  double dampener = 1; //make this 0.25 - 0.9 to make the intergral's "memory" less
  


  public:
  SubGimble();
  void Periodic();
  void InitDefaultCommand() override;
  void VoltageControl(double percentage);
  void stop(int side);
  void PIDGimbleTo(double angle);  
  void OverridePID(bool leftRight);
  void ToCentre();
  double POTPosition();
  double GetTarget();
  void PIDGimbleToLeft();
  void PIDGimbleToRight();
  void OverrideMotorLeft();
  void OverrideMotorRight();
  //void PIDEnable();
  //void PIDDisable();
  void MotorStop();
  void CustomPID(double PIDIntput);
};
