// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "CANTalon.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ADXRs450_gyro.h"
#include "WPILib.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<CANTalon> RobotMap::subDriveBaseTnxFrontLeft;
std::shared_ptr<CANTalon> RobotMap::subDriveBaseTnxRearLeft;
std::shared_ptr<CANTalon> RobotMap::subDriveBaseTnxFrontRight;
std::shared_ptr<CANTalon> RobotMap::subDriveBaseTnxRearRight;
std::shared_ptr<RobotDrive> RobotMap::subDriveBaseRobotDriveFour;
std::shared_ptr<Servo> RobotMap::subGearCatcherSrvFlap1;
std::shared_ptr<Servo> RobotMap::subGearCatcherSrvFlap2;
std::shared_ptr<SpeedController> RobotMap::subClimberSpkClimber;
std::shared_ptr<CANTalon> RobotMap::subShooterTnxShooterTop;
std::shared_ptr<CANTalon> RobotMap::subShooterTnxShooterBottom;
std::shared_ptr<CANTalon> RobotMap::subIntakeTnxIntakeRollers;
std::shared_ptr<CANTalon> RobotMap::subIntakeTnxIntakeSliders;
std::shared_ptr<SpeedController> RobotMap::subFeederVspFeederWheels;
std::shared_ptr<SpeedController> RobotMap::subFeederVspAgitatorPaddles;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

std::shared_ptr<ADXRS450_Gyro> RobotMap::subDriveBaseGyro;

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    subDriveBaseTnxFrontLeft.reset(new CANTalon(1));
    lw->AddActuator("SubDriveBase", "TnxFrontLeft", subDriveBaseTnxFrontLeft);
    
    subDriveBaseTnxRearLeft.reset(new CANTalon(2));
    lw->AddActuator("SubDriveBase", "TnxRearLeft", subDriveBaseTnxRearLeft);
    
    subDriveBaseTnxFrontRight.reset(new CANTalon(3));
    lw->AddActuator("SubDriveBase", "TnxFrontRight", subDriveBaseTnxFrontRight);
    
    subDriveBaseTnxRearRight.reset(new CANTalon(4));
    lw->AddActuator("SubDriveBase", "TnxRearRight", subDriveBaseTnxRearRight);
    
    subDriveBaseRobotDriveFour.reset(new RobotDrive(subDriveBaseTnxFrontLeft, subDriveBaseTnxRearLeft,
              subDriveBaseTnxFrontRight, subDriveBaseTnxRearRight));
    
    subDriveBaseRobotDriveFour->SetSafetyEnabled(true);
        subDriveBaseRobotDriveFour->SetExpiration(0.1);
        subDriveBaseRobotDriveFour->SetSensitivity(0.5);
        subDriveBaseRobotDriveFour->SetMaxOutput(1.0);

    subGearCatcherSrvFlap1.reset(new Servo(2));
    lw->AddActuator("SubGearCatcher", "SrvFlap1", subGearCatcherSrvFlap1);
    
    subGearCatcherSrvFlap2.reset(new Servo(3));
    lw->AddActuator("SubGearCatcher", "SrvFlap2", subGearCatcherSrvFlap2);
    
    subClimberSpkClimber.reset(new Spark(4));
    lw->AddActuator("SubClimber", "SpkClimber", std::static_pointer_cast<Spark>(subClimberSpkClimber));
    
    subShooterTnxShooterTop.reset(new CANTalon(8));
    lw->AddActuator("SubShooter", "TnxShooterTop", subShooterTnxShooterTop);
    
    subShooterTnxShooterBottom.reset(new CANTalon(7));
    lw->AddActuator("SubShooter", "TnxShooterBottom", subShooterTnxShooterBottom);
    
    subIntakeTnxIntakeRollers.reset(new CANTalon(5));
    lw->AddActuator("SubIntake", "TnxIntakeRollers", subIntakeTnxIntakeRollers);
    
    subIntakeTnxIntakeSliders.reset(new CANTalon(6));
    lw->AddActuator("SubIntake", "TnxIntakeSliders", subIntakeTnxIntakeSliders);
    
    subFeederVspFeederWheels.reset(new VictorSP(0));
    lw->AddActuator("SubFeeder", "VspFeederWheels", std::static_pointer_cast<VictorSP>(subFeederVspFeederWheels));
    
    subFeederVspAgitatorPaddles.reset(new VictorSP(1));
    lw->AddActuator("SubFeeder", "VspAgitatorPaddles", std::static_pointer_cast<VictorSP>(subFeederVspAgitatorPaddles));
    
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    subDriveBaseGyro.reset(new ADXRS450_Gyro);
    lw->AddSensor("SubDriveBase", "Gyro", subDriveBaseGyro);

    subDriveBaseGyro->Calibrate();

}
