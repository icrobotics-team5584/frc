/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include <frc/WPILib.h>
#include "subsystems/SubDriveBase.h"

enum DriveStateType { SEARCHING_FOR_SHIP, SEARCHING_FOR_HATCH,
                      AT_HATCH, HOLE_FOUND, REVERSING_TO_HATCH,
                      COMPLETE };

class CmdSeekCargoShip : public frc::Command {
   public:
    CmdSeekCargoShip(ColourSensor colourSensor, UltrasonicSensor ultrasonicSensor);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

   private:
   frc::Timer timer;
    // frc::PIDController driveController;
    DriveStateType driveState;
    bool frontClsDetected = false;
    bool midClsDetected = false;
    double drivePower = 0.6;
    ColourSensor _colourSensor;
    UltrasonicSensor _ultrasonicSensor;

};
