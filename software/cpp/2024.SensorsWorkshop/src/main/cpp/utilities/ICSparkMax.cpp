#include "utilities/ICSparkMax.h"

ICSparkMax::ICSparkMax(int deviceID, units::ampere_t currentLimit)
    : rev::CANSparkMax(deviceID, rev::CANSparkLowLevel::MotorType::kBrushless),
      ICSpark(this, GetEncoder(), currentLimit) {}

void ICSparkMax::Set(double speed) { ICSpark::SetDutyCycle(speed); }

void ICSparkMax::SetVoltage(units::volt_t output) {
  ICSpark::SetVoltage(output);
}

void ICSparkMax::StopMotor() {
  ICSpark::Stop();
  CANSparkMax::StopMotor();
}

void ICSparkMax::UseAlternateEncoder(int countsPerRev) {
    ICSpark::UseRelativeEncoder(CANSparkMax::GetAlternateEncoder(countsPerRev));
}