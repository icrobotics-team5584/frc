#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>

#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();
  static SubIntake& GetInstance() {
    static SubIntake inst;
    return inst;
  }

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Intake();
  void Stop();
  void Deploy();
  void Retract();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  ICSparkMax<> _motor{canid::intake};
  frc::DoubleSolenoid _deployPiston{frc::PneumaticsModuleType::CTREPCM, 3, 4};
};
