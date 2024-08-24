#include "utilities/ICSparkFlex.h"

ICSparkFlex::ICSparkFlex(int deviceID, units::ampere_t currentLimit)
    : rev::CANSparkFlex(deviceID, rev::CANSparkLowLevel::MotorType::kBrushless),
      ICSpark(this, GetEncoder(), currentLimit) {}

void ICSparkFlex::Set(double speed) { ICSpark::SetDutyCycle(speed); }

void ICSparkFlex::SetVoltage(units::volt_t output) {
  ICSpark::SetVoltage(output);
}

void ICSparkFlex::StopMotor() {
  ICSpark::Stop();
  CANSparkFlex::StopMotor();
}

void ICSparkFlex::UseExternalEncoder(int countsPerRev) {
    ICSpark::UseRelativeEncoder(CANSparkFlex::GetExternalEncoder(countsPerRev));
}