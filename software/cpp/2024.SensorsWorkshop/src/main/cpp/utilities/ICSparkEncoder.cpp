#include <Utilities/ICSparkEncoder.h>
#include <frc/RobotBase.h>
#include <utility>
#include <frc/smartdashboard/SmartDashboard.h>

ICSparkEncoder::ICSparkEncoder(rev::SparkRelativeEncoder&& inbuilt)
    : _inbuilt(std::move(inbuilt)) {}

double ICSparkEncoder::GetPosition() {
  switch (_selected) {
    case ABSOLUTE:
      return frc::RobotBase::IsSimulation() ? _absoluteSimPos : _absolute->GetPosition();
    case RELATIVE:
      return _relative->GetPosition();
    case INBUILT:
    default:
      return _inbuilt.GetPosition();
  }
}

double ICSparkEncoder::GetVelocity() {
  switch (_selected) {
    case ABSOLUTE:
    frc::SmartDashboard::PutNumber("arm/Encoder velocity", _absolute->GetVelocity());
      return _absolute->GetVelocity();
    case RELATIVE:
      return _relative->GetVelocity();
    case INBUILT:
    default:
      return _inbuilt.GetVelocity();
  }
}

double ICSparkEncoder::GetPositionConversionFactor() {
  return _inbuilt.GetPositionConversionFactor();
}

double ICSparkEncoder::GetVelocityConversionFactor() {
  return _inbuilt.GetVelocityConversionFactor();
}

void ICSparkEncoder::SetPosition(double pos) {
  if(_relative){
    _relative->SetPosition(pos);
  }
  _inbuilt.SetPosition(pos);
  _absoluteSimPos = pos; // Doesn't do anything for a real life absolute 
}

void ICSparkEncoder::SetConversionFactor(double rotationsToDesired) {

  if(_absolute){
     _absolute->SetPositionConversionFactor(rotationsToDesired);
     _absolute->SetVelocityConversionFactor(rotationsToDesired);
  }
  // Need to divide vel by 60 because relative encoders uses Revs per minute not Revs per second
  if(_relative){
    _relative->SetPositionConversionFactor(rotationsToDesired);
    _relative->SetVelocityConversionFactor(rotationsToDesired / 60);
  }

  _inbuilt.SetPositionConversionFactor(rotationsToDesired);
  _inbuilt.SetVelocityConversionFactor(rotationsToDesired / 60);
}

void ICSparkEncoder::UseAbsolute(rev::SparkAbsoluteEncoder&& encoder) {
  _selected = ABSOLUTE;
  _absolute = std::make_unique<rev::SparkAbsoluteEncoder>(encoder);
  SetConversionFactor(_inbuilt.GetPositionConversionFactor());
}

void ICSparkEncoder::UseRelative(rev::SparkFlexExternalEncoder&& encoder) {
  _selected = RELATIVE;
  _relative = std::make_unique<rev::SparkFlexExternalEncoder>(encoder);
  SetConversionFactor(_inbuilt.GetPositionConversionFactor());
}

void ICSparkEncoder::UseRelative(rev::SparkMaxAlternateEncoder&& encoder) {
  _selected = RELATIVE;
  _relative = std::make_unique<rev::SparkMaxAlternateEncoder>(encoder);
  SetConversionFactor(_inbuilt.GetPositionConversionFactor());
}

const rev::MotorFeedbackSensor& ICSparkEncoder::GetPIDFeedbackDevice() {
  switch (_selected) {
    case ABSOLUTE:
      return *_absolute;
    case RELATIVE:
      return *_relative;
    case INBUILT:
    default:
      return _inbuilt;
  }
}