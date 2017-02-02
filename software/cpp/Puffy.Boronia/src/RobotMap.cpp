// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<CANTalon> RobotMap::shooterFlywheelsCANTalonShooterMotorRear;
std::shared_ptr<CANTalon> RobotMap::shooterFlywheelsCANTalonShooterMotorFront;
std::shared_ptr<CANTalon> RobotMap::pickupRollerCANTalonFrontRoller;
std::shared_ptr<DigitalInput> RobotMap::pickupRollerLimitSwitchBallOnboard;
std::shared_ptr<CANTalon> RobotMap::feedRollerCANTalonRearRoller;
std::shared_ptr<DoubleSolenoid> RobotMap::frontArmDoubleSolenoidLeft;
std::shared_ptr<DoubleSolenoid> RobotMap::frontArmDoubleSolenoidRight;
std::shared_ptr<DoubleSolenoid> RobotMap::shooterArmDoubleSolenoidRear;
std::shared_ptr<CANTalon> RobotMap::driveBaseCANTalonFrontRight;
std::shared_ptr<CANTalon> RobotMap::driveBaseCANTalonFrontLeft;
std::shared_ptr<CANTalon> RobotMap::driveBaseCANTalonRearLeft;
std::shared_ptr<CANTalon> RobotMap::driveBaseCANTalonRearRight;
std::shared_ptr<RobotDrive> RobotMap::driveBaseRobotDriveFourControllers;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    shooterFlywheelsCANTalonShooterMotorRear.reset(new CANTalon(5));
    lw->AddActuator("ShooterFlywheels", "CANTalonShooterMotorRear", shooterFlywheelsCANTalonShooterMotorRear);
    
    shooterFlywheelsCANTalonShooterMotorFront.reset(new CANTalon(6));
    lw->AddActuator("ShooterFlywheels", "CANTalonShooterMotorFront", shooterFlywheelsCANTalonShooterMotorFront);
    
    pickupRollerCANTalonFrontRoller.reset(new CANTalon(7));
    lw->AddActuator("PickupRoller", "CANTalonFrontRoller", pickupRollerCANTalonFrontRoller);
    
    pickupRollerLimitSwitchBallOnboard.reset(new DigitalInput(0));
    lw->AddSensor("PickupRoller", "LimitSwitchBallOnboard", pickupRollerLimitSwitchBallOnboard);
    
    feedRollerCANTalonRearRoller.reset(new CANTalon(8));
    lw->AddActuator("FeedRoller", "CANTalonRearRoller", feedRollerCANTalonRearRoller);
    
    frontArmDoubleSolenoidLeft.reset(new DoubleSolenoid(0, 4, 5));
    lw->AddActuator("FrontArm", "DoubleSolenoidLeft", frontArmDoubleSolenoidLeft);
    
    frontArmDoubleSolenoidRight.reset(new DoubleSolenoid(0, 2, 3));
    lw->AddActuator("FrontArm", "DoubleSolenoidRight", frontArmDoubleSolenoidRight);
    
    shooterArmDoubleSolenoidRear.reset(new DoubleSolenoid(0, 0, 1));
    lw->AddActuator("ShooterArm", "DoubleSolenoidRear", shooterArmDoubleSolenoidRear);
    
    driveBaseCANTalonFrontRight.reset(new CANTalon(3));
    lw->AddActuator("DriveBase", "CANTalonFrontRight", driveBaseCANTalonFrontRight);
    
    driveBaseCANTalonFrontLeft.reset(new CANTalon(1));
    lw->AddActuator("DriveBase", "CANTalonFrontLeft", driveBaseCANTalonFrontLeft);
    
    driveBaseCANTalonRearLeft.reset(new CANTalon(2));
    lw->AddActuator("DriveBase", "CANTalonRearLeft", driveBaseCANTalonRearLeft);
    
    driveBaseCANTalonRearRight.reset(new CANTalon(4));
    lw->AddActuator("DriveBase", "CANTalonRearRight", driveBaseCANTalonRearRight);
    
    driveBaseRobotDriveFourControllers.reset(new RobotDrive(driveBaseCANTalonFrontLeft, driveBaseCANTalonRearLeft,
              driveBaseCANTalonFrontRight, driveBaseCANTalonRearRight));
    
    driveBaseRobotDriveFourControllers->SetSafetyEnabled(true);
        driveBaseRobotDriveFourControllers->SetExpiration(0.1);
        driveBaseRobotDriveFourControllers->SetSensitivity(0.5);
        driveBaseRobotDriveFourControllers->SetMaxOutput(1.0);



    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}