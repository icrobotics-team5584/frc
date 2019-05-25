/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdPidArm.h"

#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>

CmdPidArm::CmdPidArm()
    : PIDSubsystem("CmdPidArm", 1.0, 0.0, 0.0) {
  // Use these to get going:
  // SetSetpoint() -  Sets where the PID controller should move the system
  //                  to
  // Enable() - Enables the PID controller.
}

double CmdPidArm::ReturnPIDInput() {
  // Return your input value for the PID loop
  // e.g. a sensor, like a potentiometer:
  // yourPot->SetAverageVoltage() / kYourMaxVoltage;

  /* Okay so usually for a case like this we would use a potentiometer (they are like encoders but are not continuous however they
  * are used because they track angle despite being turned off).
  * Recently we discovered that CTRE mag encoders also have the ability to return 'absolute' positioning, so that is probably
  * what we will be using for this robot. (mechanical team does not enjoy mounting potentiometers)
  * The CTRE mag encoders, will always track absolute positioning and quadrature positioning simultaneously
  * If you don't know what quadrature encoders are:
  * So basically there are two types of encoders: Quadrature and non-quadrature (i don't really know what they're called)
  * A non quadrature only has one data channel, where let's just say it sends a pulse to the computer to signify 1 rotation.
  * A quadrature encoder has 2 data channels, A and B. Insead of only measuring distance, they are also capable of returning diretion.
  * 
  * Anyway CTRE encoders in absolute mode. We have no idea how to do it, good luck in figuring it out :P . I suspect it is to do 
  * with something in the firmware. You will need to test what changing the firmware does.
  *
  */
  return 0;
}

void CmdPidArm::UsePIDOutput(double output) {
  // Use output to drive your system, like a motor
  // e.g. yourMotor->Set(output);
  CmdPidArm::srxArm->Set(output);
}

void CmdPidArm::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  srxArm.reset(new WPI_TalonSRX(_talon));
}
