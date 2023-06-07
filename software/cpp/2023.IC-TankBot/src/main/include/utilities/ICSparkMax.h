#pragma once

#include <frc/Notifier.h>
#include <frc/Timer.h>
#include <frc/controller/PIDController.h>
#include <frc/simulation/SimDeviceSim.h>
#include <frc/trajectory/TrapezoidProfile.h>
#include <hal/simulation/SimDeviceData.h>
#include <rev/CANSparkMax.h>
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

/**
 * Wrapper around the Rev CANSparkMax class with some convenience features.
 * - Brushless motor type assumed
 * - 20 Amp default current limit
 * - Better simulation support (see GetSimVoltage() and UpdateSimEncoder())
 * - Uses C++ units:
 *   > Position units can be set using tempalte argument
 *   > Velocity and acceleration units are based on change in position per second
 *   > Defaults are turns for pos, turns per sec for vel and turns per sec per sec for acceleration
 * - Encoder and pid functions are built into this class
 */
template <class Position = units::turn>
class ICSparkMax : public rev::CANSparkMax, wpi::Sendable {
 public:
  // Setup velcoity and acceleration units based on Position
  using Velocity = units::compound_unit<Position, units::inverse<units::seconds>>;
  using Acceleration = units::compound_unit<Velocity, units::inverse<units::seconds>>;
  using Position_t = units::unit_t<Position>;
  using Velocity_t = units::unit_t<Velocity>;
  using Acceleration_t = units::unit_t<Acceleration>;

  /**
   * Create a new object to control a SPARK MAX motor controller, with added convenience features.
   *
   * @param deviceID The device CAN id
   * @param currentLimit Value used for spark max smart current limiting
   */
  ICSparkMax(int deviceID, units::ampere_t currentLimit = 20_A);

  /**
   * Sets position of motor
   * 
   * @param position What to set the position to
  */
  void SetPosition(Position_t position);

  /**
   * Sets a closed loop position target (aka reference or goal) for the motor to drive to.
   *
   * @param target The target position drive to.
   *
   * @param arbFeedforward A voltage from -32.0V to 32.0V which is applied to the motor after the
   * result of the specified control mode. This value is added after the control mode, but before
   * any current limits or ramp rates
   */
  void SetPositionTarget(Position_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Sets a closed loop position target (aka reference or goal) for the motor to drive to using
   * the Spark Max's Smart Motion control mode.
   * This generates a profiled movement that accelerates and decelerates in a controlled way. This
   * can reduce ware on components and is often much easier to tune. For anything beyond prototypes
   * and the simplest of mechanisms, this is preferred over regular position control. In this mode,
   * you are actually controlling the velocity of the motor to follow a trapezoid (speeding up,
   * staying constant, then slowing down) and as such the PID values should be tuned to follow a
   * velocity target. Controlling velocity also allows us to use the WPILib feedforward classes.
   *
   * @param target The target position drive to.
   *
   * @param arbFeedforward A voltage from -32.0V to 32.0V which is applied to the motor after the
   * result of the specified control mode. This value is added after the control mode, but before
   * any current limits or ramp rates
   */
  void SetSmartMotionTarget(Position_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Sets the closed loop target (aka reference or goal) for the motor to drive to.
   *
   * @param target The target position drive to.
   *
   * @param arbFeedforward A voltage from -32.0V to 32.0V which is applied to the motor after the
   * result of the specified control mode. This value is added after the control mode, but before
   * any current limits or ramp rates
   */
  void SetVelocityTarget(Velocity_t target, units::volt_t arbFeedForward = 0.0_V);

  /**
   * Gets the current closed loop position target if there is one. Zero otherwise.
   */
  Position_t GetPositionTarget() { return _positionTarget; };

  /**
   * Gets the current closed loop velocity target if there is one. Zero otherwise
   */
  Velocity_t GetVelocityTarget() {
    return GetControlType() == Mode::kSmartMotion ? GetCurrentSMVelocity() : _velocityTarget;
  };

  /**
   * Get the closed loop position error (current position - target position) if there is one. 
   * Zero otherwise.
   */
  Position_t GetPosError() { return GetPosition() - _positionTarget; }

  /**
   * Get the closed loop velocity error (current velocity - target velocity) if there is one.
   * Zero otherwise.
   */
  Velocity_t GetVelError() { return GetVelocity() - _velocityTarget; }

  /**
   * Calculates how much voltage the spark max would be giving to the attached motor given its
   * current control type and PID configuration. Use this in conjunction with one of WPILib's
   * physics simulation classes.
   * (https://docs.wpilib.org/en/stable/docs/software/wpilib-tools/robot-simulation/physics-sim.html)
   */
  units::volt_t GetSimVoltage();

  /**
   * Due to REVLib archetecture, we need to calculate our own power output when in simulation using
   * a stored copy of the PID configuration. Call this after changing PID configuration to keep the
   * simulation in sync with the Spark Max's internal values. This is called automatically when
   * Set...Target() and SetPIDFF() is called.
   */
  void SyncSimPID();

  /**
   * It is the user's responsibility to update the encoder position and
   * velocity when in simulation. To do this, use WPILib's physics simulation
   * classes at
   * https://docs.wpilib.org/en/stable/docs/software/wpilib-tools/robot-simulation/physics-sim.html
   * to get the position and velocity of the mechanism attached to this motor.
   */
  void UpdateSimEncoder(Position_t position, Velocity_t velocity);

  /**
   * Gets the current closed loop control type.
   */
  rev::CANSparkMax::ControlType GetControlType() { return _controlType; };

  /**
   * Get the velocity of the motor.
   */
  Velocity_t GetVelocity();

  /**
   * Get the position of the motor.
   */
  Position_t GetPosition() { return Position_t{_encoder->GetPosition()}; };

  /**
   * Common interface to stop the motor until Set is called again or closed loop control is started.
   */
  void StopMotor() override;

  /**
   * Common interface for setting the speed of a speed controller.
   *
   * @param speed The speed to set. Value should be between -1.0 and 1.0.
   */
  void Set(double speed) override;

  /**
   * Common interface for setting the voltage of a speed controller.
   *
   * @param output The voltage to set.
   */
  void SetVoltage(units::volt_t output) override;

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
  void ConfigSmartMotion(Velocity_t maxVelocity, Acceleration_t maxAcceleration,
                         Position_t tolerance);

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
   * @param FF The Feed Forward gain value, must be positive. This is multiplied
   * by the target before being added to the final output power.
   */
  void SetPIDFF(double P, double I, double D, double FF = 0.0);

  /**
   * Set the position of the encoder.
   */
  void SetEncoderPosition(Position_t position);

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
   * Switch to using an external encoder connected to the alternate encoder data port on the SPARK
   * MAX. The pins on this port are defined as:
   *    > Pin 4 (Forward Limit Switch): Index
   *    > Pin 6 (Multi-function): Encoder A
   *    > Pin 8 (Reverse Limit Switch): Encoder B
   *
   * This call will disable support for the limit switch inputs.
   *
   * @param countsPerRev The number of encoder counts per revolution. Leave as
   * default for the REV through bore encoder.
   */
  void UseAlternateEncoder(int countsPerRev = 8192);

  /**
   * Switch to using an external absolute encoder connected to the data port on the SPARK MAX. 
   * 
   * @param encoder The encoder to use as a feedback sensor for closed loop control
   */
  void UseAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder& encoder);

  /**
   * Set the minimum and maximum input value for PID Wrapping with position closed loop
   * control.
   *
   * @param max The maximum input value
   * @param min The minimum input value
   */
  void EnableSensorWrapping(double min, double max);

  /**
   * Set the control type before giving the controller any targets. Run this before setting PIDF
   * gain so the ICSparkMax can convert your PIDF gains into the correct position or velocity units.
   * 
   * @param controlType The control type. Options include position, velocity, smartmotion, etc.
   */
  void SetClosedLoopControlType(rev::CANSparkMax::ControlType controlType) {
    SetInternalControlType(controlType);
  }

  // Sendable setup, called automatically when this is passed into smartDashbaord::PutData()
  void InitSendable(wpi::SendableBuilder& builder) override;

  // Delete some SPARK MAX functions so user doesn't get multiple copies of friend objects.
  rev::SparkMaxRelativeEncoder GetEncoder() = delete;
  rev::SparkMaxAlternateEncoder GetAlternateEncoder() = delete;
  rev::SparkMaxPIDController GetPIDController() = delete;

 private:
  using Mode = rev::CANSparkMax::ControlType;

  // Conversion helpers
  Position_t SparkRevsToPos(double revs) {
    return Position_t{revs * _encoder->GetPositionConversionFactor()};
  }
  Velocity_t SparkRPMToVel(double rpm) {
    return Velocity_t{rpm * _encoder->GetVelocityConversionFactor()};
  }
  Acceleration_t SparkRPMpsToAccel(double accel) {
    return Acceleration_t{accel * _encoder->GetVelocityConversionFactor()};
  }
  double PosToSparkRevs(Position_t pos) {
    return pos.value() / _encoder->GetPositionConversionFactor();
  }
  double VelToSparkRPM(Velocity_t vel) {
    return vel.value() / _encoder->GetVelocityConversionFactor();
  }
  double AccelToSparkRPMps(Acceleration_t accel) {
    return accel.value() / _encoder->GetVelocityConversionFactor();
  }

  // Related REVLib objects
  rev::SparkMaxPIDController _pidController{CANSparkMax::GetPIDController()};
  std::unique_ptr<rev::RelativeEncoder> _encoder =
      std::make_unique<rev::SparkMaxRelativeEncoder>(CANSparkMax::GetEncoder());

  // PID simulation configuration
  bool _updatingTargetFromSendable = false;
  Position_t _positionTarget{0};
  Velocity_t _velocityTarget{0};
  units::volt_t _voltageTarget{0};
  units::volt_t _arbFeedForward = 0.0_V;
  frc::PIDController _simController{0, 0, 0};
  double _FF{0};
  frc::TrapezoidProfile<Position> _simSmartMotionProfile{
      {Velocity_t{0}, Acceleration_t{0}},  // constraints
      {Position_t{0}, Velocity_t{0}}       // goal states
  };
  frc::Timer _smartMotionProfileTimer;
  Mode _controlType = Mode::kDutyCycle;
  void SetInternalControlType(Mode controlType);
  void GenerateSMProfile();
  Velocity_t GetCurrentSMVelocity();
  Velocity_t _simVelocity = Velocity_t{0};

  // Sim device values (stuff that shows under Other Devices on Glass)
  frc::sim::SimDeviceSim _simDeviceSim{"SPARK MAX ", GetDeviceId()};
  hal::SimInt _simControlMode = _simDeviceSim.GetInt("Control Mode");

  double _minPidOutput = -1;
  double _maxPidOutput = 1;

};

#include "ICSparkMax.tpp"

