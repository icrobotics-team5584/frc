#pragma once

#include <rev/CANSparkMax.h>
#include <rev/CANSparkFlex.h>
#include <rev/RelativeEncoder.h>
#include <memory>

class ICSparkEncoder {
 public:
  ICSparkEncoder(rev::SparkRelativeEncoder&& inbuilt);
  enum EncoderType { INBUILT, ABSOLUTE, RELATIVE };

  void SetPosition(double pos);
  void SetConversionFactor(double rotationsToDesired);
  void UseRelative(rev::SparkMaxAlternateEncoder&& encoder);
  void UseRelative(rev::SparkFlexExternalEncoder&& encoder);
  void UseAbsolute(rev::SparkAbsoluteEncoder&& encoder);
  
  double GetPosition();
  double GetVelocity();
  double GetPositionConversionFactor();
  double GetVelocityConversionFactor();
  const rev::MotorFeedbackSensor& GetPIDFeedbackDevice();

 private:
  rev::SparkRelativeEncoder _inbuilt;
  std::unique_ptr<rev::SparkAbsoluteEncoder> _absolute;
  std::unique_ptr<rev::RelativeEncoder> _relative;
  double _absoluteSimPos = 0;
  EncoderType _selected = INBUILT;
};