#pragma once

#include <rev/CANSparkMax.h>

#include "utilities/ICSparkBase.h"

/**
 * Wrapper around the Rev CANSparkMax class with some convenience features.
 * - Brushless motor type assumed
 * - Required Current Limit Setting
 * - Better simulation support (see ICSpark::GetSimVoltage() and ICSpark::UpdateSimEncoder())
 * - Uses C++ units
 * - Encoder and pid functions are built into this class
 */
class ICSparkMax : public rev::CANSparkMax, public ICSpark {
 public:
  ICSparkMax(int deviceID, units::ampere_t currentLimit);
  static constexpr int NEO_ENCODER_RESOLUTION = 42;

  /**
   * Stop the motor until Set is called again or closed loop control is started.
   */
  void StopMotor() override;

  /**
   * Sets the duty cycle of a speed controller.
   *
   * @param speed The duty cycle to set. Value should be between -1.0 and 1.0.
   */
  void Set(double speed) override;

  /**
   * Sets the voltage of a speed controller.
   *
   * @param output The voltage to set.
   */
  void SetVoltage(units::volt_t output) override;

  /**
   * Use an alternate quadrature (relative) encoder connected to the Spark Max's
   * data port as the feedback device. To use an absolute encoder, see
   * UseAbsoluteEncoder() in ICSpark. This will be used for dashboard displays and
   * PID feedback. The pins of the data port are defined as:
   *
   * Pin 4 (Forward Limit Switch): Index
   * Pin 6 (Multi-function): Encoder A
   * Pin 8 (Reverse Limit Switch): Encoder B
   *
   * This call will disable support for the limit switch inputs.
   *
   * @param countsPerRev Number of encoder counts per revolution of the sensor.
   * Defaulted to 8192 which is the value for a REV throughbore encoder.
   */
  void UseAlternateEncoder(int countsPerRev = 8192);
};