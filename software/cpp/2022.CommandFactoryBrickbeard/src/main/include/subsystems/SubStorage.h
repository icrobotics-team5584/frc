#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>

#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubStorage : public frc2::SubsystemBase {
 public:
  SubStorage();
  static SubStorage& GetInstance() {
    static SubStorage inst;
    return inst;
  }

  void Periodic() override;
  void Start();
  void Stop();
  void ReleaseBall();
  void BlockBall();

 private:
  ICSparkMax<> _motor{canid::storage};
  frc::DoubleSolenoid _releasePiston{frc::PneumaticsModuleType::CTREPCM, 1, 2};
};
