#include "subsystems/SubRollerIntakeBar.h"
#include "Robot.h"
#include "commands/CmdMoveRollerIntakeBar.h"


SubRollerIntakeBar::SubRollerIntakeBar() : Subsystem("ExampleSubsystem") {
  // Set PID constants
  const double kP = 0.01;
  const double kI = 0;
  const double kD = 0;
  
  srxRollerBar = Robot::_robotMap->srxRollerIntakeBar;
  srxRollerBar->SetSelectedSensorPosition(0);

  // Set up PIDController
  pidsrcRoller.reset(new PidsrcRoller());
  pidoutRoller.reset(new PidoutRoller());
  positionController.reset(new PIDController(kP, kI, kD, pidsrcRoller.get(), pidoutRoller.get()));
  positionController->SetSetpoint(7); // Measured in degrees
  positionController->SetAbsoluteTolerance(5); // Measured in degrees
  positionController->SetOutputRange(-0.5, 0.5);
  frc::SmartDashboard::PutData("roller intake bar PID controller", positionController.get());

  // Place testing command to dashboard
  // frc::SmartDashboard::PutData("Move roller intake bar", new CmdMoveRollerIntakeBar(OUT));
}


/*
 * Set the default command for a subsystem here
 */
void SubRollerIntakeBar::InitDefaultCommand() {
  // SetDefaultCommand(new MySpecialCommand());
}


/*
 * Enables or disables the PID loop that controls the bar position. 
 */
void SubRollerIntakeBar::SetPIDEnabled(bool enabled) {
  positionController->SetEnabled(enabled);
}


/*
 * Uses an angle to set the target position for the bar. 0 degrees is inside the robot, while
 * 165 degrees is the out position. It is recommended that these extremes are not used to avoid
 * the bar colliding with any other part of the robot. Anything outside this range will be 
 * constricted to this range. 
 */
void SubRollerIntakeBar::SetSetpoint(double angle) {
  if (angle > 165) {
    angle = 165;
  } else if (angle < 0) {
    angle = 0;
  }
  positionController->SetSetpoint(angle);
}


/*
 * Uses one of the three set positions to set the target position for the bar. The options are
 * OUT, UP, and IN. Make sure to #include "subsystems/subRollerIntakeBar.h" to use these options.
 */
void SubRollerIntakeBar::SetSetpoint(RollerPosition rollerPosition) {
  switch (rollerPosition) {
    case OUT:
      SetSetpoint(160);
      break;
    case UP:
      SetSetpoint(90);
      break;
    case IN:
      SetSetpoint(7);
      break;
  }
}


/*
 * Gets the current angle of the bar in degrees. 0 degrees represents the bar completely stowed in
 * the robot, while 165 degrees represents the bar completely deployed. Note that encoder slip 
 * sometimes results in the angle reading 7 degrees when stowed.
 */
double SubRollerIntakeBar::GetAngle() {
  return srxRollerBar->GetSelectedSensorPosition(0) / SENSOR_UNITS_PER_DEGREE;
}


/*
 * Checked whether the current angle is within the tolerance range set in this subsystem's
 * constructor.
 */
bool SubRollerIntakeBar::OnTarget() {
  return positionController->OnTarget();
}


/*
 * This private function is used by the PID controller to give a power percentage to the motor that
 * controls the bar.
 */
void SubRollerIntakeBar::MoveBar(double power) {
  srxRollerBar->Set(power);
}
