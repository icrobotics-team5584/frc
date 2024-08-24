#pragma once

#include <rev/CANSparkBase.h>
#include <frc/controller/PIDController.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <units/acceleration.h>
#include <units/length.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/time.h>
#include <units/current.h>
#include <units/velocity.h>
#include <wpi/sendable/Sendable.h>
#include <wpi/sendable/SendableBuilder.h>
#include "utilities/ICSparkEncoder.h"

/**
 * Wrapper around the Rev CANSparkBase class with some convenience features.
 * - Required Current Limit Setting
 * - Better simulation support (see GetSimVoltage() and UpdateSimEncoder())
 * - Uses C++ units
 * - Encoder and pid functions are built into this class
 */
class ICSpark : public wpi::Sendable {
 public:
  enum class ControlType {
    kDutyCycle = (int)rev::CANSparkLowLevel::ControlType::kDutyCycle,
    kVelocity = (int)rev::CANSparkLowLevel::ControlType::kVelocity,
    kVoltage = (int)rev::CANSparkLowLevel::ControlType::kVoltage,
    kPosition = (int)rev::CANSparkLowLevel::ControlType::kPosition,
    kSmartMotion = (int)rev::CANSparkLowLevel::ControlType::kSmartMotion,
    kCurrent = (int)rev::CANSparkLowLevel::ControlType::kCurrent,
    kMotionProfile = 10
  };

  using VoltsPerTps = units::unit_t<units::compound_unit<
      units::volts, units::inverse<units::turns_per_second>>>;
  using VoltsPerTpsSq = units::unit_t<units::compound_unit<
      units::volts, units::inverse<units::turns_per_second_squared>>>;

  /**
   * Create a new object to control a SPARK motor controller.
   *
   * @param currentLimit Value used for spark smart current limiting
   * @param inbultEncoder rvalue reference to the encoder built into the NEO
   * @param spark Reference to the spark to control
   */
  ICSpark(rev::CANSparkBase* spark,
              rev::SparkRelativeEncoder&& inbuiltEncoder,
              units::ampere_t currentLimit);

  /**
   * Sets position of motor
   *
   * @param position What to set the position to
   */
  void SetPosition(units::turn_t position);

  /**
   * Sets a closed loop position target (aka reference or goal) for the motor to drive to.
   *
   * @param target The target position drive to.
   *
   * @param arbFeedforward A voltage from -32.0V to 32.0V which is applied to the motor after the
   * result of the specified control mode. This value is added after the control mode, but before
   * any current limits or ramp rates
   */
  void SetPositionTarget(units::turn_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Sets a closed loop position target (aka reference or goal) for the motor to
   * drive to using the Spark Max's Smart Motion control mode. This generates a
   * profiled movement that accelerates and decelerates in a controlled way.
   * This can reduce ware on components, limit current draw and is can be easier
   * to tune. In this mode, you are actually controlling the velocity of the
   * motor to follow a trapezoid (speeding up, staying constant, then slowing
   * down) and as such the PID values should be tuned to follow a velocity
   * target. Also consider using SetMotionProfileTarget() to compute a profile
   * on the RoboRio and perform feedback control based on position.
   *
   * @param target The target position drive to.
   *
   * @param arbFeedforward A voltage from -32.0V to 32.0V which is applied to
   * the motor after the result of the specified control mode. This value is
   * added after the control mode, but before any current limits or ramp rates
   */
  void SetSmartMotionTarget(units::turn_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Sets a closed loop position target (aka reference or goal) for the motor to
   * drive to using a motion profile computed onboard the RoboRio and followed
   * using the Spark Max's onboard PID position control.
   * This generates a profiled movement that accelerates and decelerates in a controlled way. This
   * can reduce ware on components, limit current draw and can be easier to tune.
   * 
   */
  void SetMotionProfileTarget(units::turn_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Sets the closed loop target (aka reference or goal) for the motor to drive to.
   *
   * @param target The target position drive to.
   *
   * @param arbFeedforward A voltage from -32.0V to 32.0V which is applied to the motor after the
   * result of the specified control mode. This value is added after the control mode, but before
   * any current limits or ramp rates
   */
  void SetVelocityTarget(units::turns_per_second_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Update motion profile targets and feedforward calculations. This is
   * required to be called periodically when you use kG gains or a motion
   * profile.
   * This only has an effect when in one of the following modes: Motion Profile,
   * Smart Motion, Position, Velocty.
   *
   * @param loopTime The frequency at which this is being called. 20ms is the
   * default loop time for WPILib periodic functions. Generally, faster loop
   * times result in smoother controls at the cost of processing time.
   */
  void UpdateControls(units::second_t loopTime = 20_ms);

  /**
   * Calculate how many volts to send to the motor from the feedforward model.
   * (Before any feedback control is applied).
  */
  units::volt_t CalculateFeedforward(units::turns_per_second_squared_t accelerationTarget = 0_tr_per_s_sq);

  /**
   * Gets the current closed loop position target if there is one. Zero otherwise.
   */
  units::turn_t GetPositionTarget() { return _positionTarget; };

  /**
   * Gets the current closed loop velocity target if there is one. Zero otherwise
   */
  units::turns_per_second_t GetVelocityTarget() { return _velocityTarget; };

  /**
   * Get the closed loop position error (current position - target position) if there is one.
   * Zero otherwise.
   */
  units::turn_t GetPosError() { return GetPosition() - _positionTarget; }

  /**
   * Get the closed loop velocity error (current velocity - target velocity) if there is one.
   * Zero otherwise.
   */
  units::turns_per_second_t GetVelError() { return GetVelocity() - _velocityTarget; }

  /**
   * Calculates how much voltage the spark max would be giving to the attached motor given its
   * current control type and PID configuration. Use this in conjunction with one of WPILib's
   * physics simulation classes.
   * (https://docs.wpilib.org/en/stable/docs/software/wpilib-tools/robot-simulation/physics-sim.html)
   */
  units::volt_t GetSimVoltage();

  /**
   * It is the user's responsibility to update the encoder position and
   * velocity when in simulation. To do this, use WPILib's physics simulation
   * classes at
   * https://docs.wpilib.org/en/stable/docs/software/wpilib-tools/robot-simulation/physics-sim.html
   * to get the position and velocity of the mechanism attached to this motor.
   */
  void UpdateSimEncoder(units::turn_t position, units::turns_per_second_t velocity);

  /**
   * Gets the current closed loop control type.
   */
  ControlType GetControlType() { return _controlType; };

  /**
   * Get the velocity of the motor.
   */
  units::turns_per_second_t GetVelocity();

  /**
   * Get the position of the motor.
   */
  units::turn_t GetPosition() { return units::turn_t{_encoder.GetPosition()}; };

  /**
   * Common interface to stop the motor until Set is called again or closed loop control is started.
   */
  void Stop();

  /**
   * Sets the duty cycle of a speed controller.
   *
   * @param speed The duty cycle to set. Value should be between -1.0 and 1.0.
   */
  void SetDutyCycle(double speed);

  /**
   * Sets the voltage of a speed controller.
   *
   * @param output The voltage to set.
   */
  void SetVoltage(units::volt_t output);

  /**
   * Configure the constrains for the SparkMax's Smart Motion control mode. Maximum velocity,
   * maximum acceleration, and position tolerance must be set.
   *
   * @param maxVelocity The maxmimum velocity for the motion profile.
   *
   * @param maxAcceleration The maxmimum acceleration for the motion profile.
   *
   * @param tolerance When the position of the motor is within tolerance, the control mode will stop
   * applying power (arbitary feedforward can still apply power).
   */
  void ConfigMotion(units::turns_per_second_t maxVelocity,
                         units::turns_per_second_squared_t maxAcceleration,
                         units::turn_t tolerance);

  /**
   * Set the conversion factor for position, velocity and acceleration of the encoder. The native
   * position units of rotations will be multipled by this number before being used or returned.
   * Velocity and acceleration conversion factors will be derived from this (as position units per
   * second for velocity and velocity units per second for acceleration)
   */
  void SetConversionFactor(double rotationsToDesired);

  /**
   * Set the Proportional, Integral, Derivative and static FeedForward gain constants of the PIDF
   * controller on the SPARK MAX. This uses the Set Parameter API and should be used infrequently.
   * The parameters do not presist unless burnFlash() is called.
   *
   * @param P The proportional gain value, must be positive
   * @param I The Integral gain value, must be positive
   * @param D The Derivative gain value, must be positive
   * by the target before being added to the final output power.
   */
  void SetFeedbackGains(double P, double I, double D);
  void SetFeedbackProportional(double P);
  void SetFeedbackIntegral(double I);
  void SetFeedbackDerivative(double D);

  void SetFeedforwardGains(
      units::volt_t S = 0_V, 
      units::volt_t G = 0_V,
      bool gravityIsRotational = false,
      VoltsPerTps V = 0_V / 1_tps,
      VoltsPerTpsSq A = 0_V / 1_tr_per_s_sq);
  void SetFeedforwardStaticFriction(units::volt_t S);
  void SetFeedforwardLinearGravity(units::volt_t linearG);
  void SetFeedforwardRotationalGravity(units::volt_t rotationalG);
  void SetFeedforwardVelocity(VoltsPerTps V);
  void SetFeedforwardAcceleration(VoltsPerTpsSq A);

  /**
   * Set the min amd max output for the closed loop mode.
   *
   * This uses the Set Parameter API and should be used infrequently. The parameter does not presist
   * unless burnFlash() is called.
   *
   * @param minOutputPercent Power minimum allowed (-1.0 to 1.0)
   *
   * @param maxOutputPercent Power maximum allowed (-1.0 to 1.0)
   */
  void SetClosedLoopOutputRange(double minOutputPercent, double maxOutputPercent);

  /**
   * Switch to using an external absolute encoder connected to the data port on
   * the SPARK. To use a relative encoder, check the Spark Max and Spark Flex
   * specific implimentation. The Max uses "Alternate encoders" while the Flex
   * uses "External encoders"
   *
   * @param zeroOffset the position that is reported as zero. It is influenced
   * by the absolute encoder's position conversion factor, and whether it is
   * inverted. So set those parameters before calling this.
   */
  void UseAbsoluteEncoder(units::turn_t zeroOffset = 0_tr);

  /**
   * Set the minimum and maximum input value for PID Wrapping with position closed loop
   * control.
   *
   * @param max The maximum input value
   * @param min The minimum input value
   */
  void EnableClosedLoopWrapping(units::turn_t min, units::turn_t max);

  /**
   * Check whether the motor is on its position target, within a given tolerance.
   *
   * @param tolerance The tolerance to be considered on target
   */
  bool OnPosTarget(units::turn_t tolerance) { return units::math::abs(GetPosError()) < tolerance; }

  /**
   * Check whether the motor is on its velocity target, within a given tolerance.
   *
   * @param tolerance The tolerance to be considered on target
   */
  bool OnVelTarget(units::turns_per_second_t tolerance) {
    return units::math::abs(GetVelError()) < tolerance;
  }

  // Sendable setup, called automatically when this is passed into smartDashbaord::PutData()
  void InitSendable(wpi::SendableBuilder& builder) override;
  
 protected:
  // Use a relative (alternarte for Max, external for Flex) encoder as the feedback device.
  template <std::derived_from<rev::RelativeEncoder> RelEncoder>
  void UseRelativeEncoder(RelEncoder&& encoder) {
    _encoder.UseRelative(std::move(encoder));
    _pidController.SetFeedbackDevice(_encoder.GetPIDFeedbackDevice());
  }

 private:
  rev::CANSparkBase* _spark;
  using MPState = frc::TrapezoidProfile<units::turns>::State;
  rev::CANSparkLowLevel::ControlType GetREVControlType();

  // Related REVLib objects
  rev::SparkPIDController _pidController{_spark->GetPIDController()};
  ICSparkEncoder _encoder;

  // Feedforward gains
  units::volt_t _feedforwardStaticFriction = 0_V;
  units::volt_t _feedforwardLinearGravity = 0_V;
  units::volt_t _feedforwardRotationalGravity = 0_V;
  VoltsPerTps _feedforwardVelocity = 0_V / 1_tps;
  VoltsPerTpsSq _feedforwardAcceleration = 0_V / 1_tr_per_s_sq;

  // PID simulation configuration
  bool _updatingTargetFromSendable = false;
  units::turn_t _positionTarget{0};
  units::turns_per_second_t _velocityTarget{0};
  units::volt_t _voltageTarget{0};
  units::volt_t _arbFeedForward = 0.0_V;
  frc::PIDController _simController{0, 0, 0};
  frc::TrapezoidProfile<units::turns> _motionProfile{
      {units::turns_per_second_t{0},
       units::turns_per_second_squared_t{0}}  // constraints updated by SetMotionConfig
  };
  ControlType _controlType = ControlType::kDutyCycle;
  void SetInternalControlType(ControlType controlType);
  MPState CalcNextMotionTarget(units::second_t lookahead = 20_ms);
  MPState _latestMotionTarget;
  bool InMotionMode();
  units::turns_per_second_t _simVelocity = units::turns_per_second_t{0};

  double _minPidOutput = -1;
  double _maxPidOutput = 1;
};
