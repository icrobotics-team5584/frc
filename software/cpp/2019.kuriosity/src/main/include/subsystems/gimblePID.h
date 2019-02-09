#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>

class gimblePID : public frc::PIDOutput {
 private:
 

 public:
  gimblePID();
  void PIDWrite(double output);
	virtual ~gimblePID();
};
