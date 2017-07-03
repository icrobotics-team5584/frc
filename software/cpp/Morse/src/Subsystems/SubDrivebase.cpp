// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"


#include "SubDrivebase.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "../Commands/CmdJoystickDrive.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

SubDrivebase::SubDrivebase() : Subsystem("SubDrivebase") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    cANTalonLeft = RobotMap::subDrivebaseCANTalonLeft;
    cANTalonRight = RobotMap::subDrivebaseCANTalonRight;
    dRV = RobotMap::subDrivebaseDRV;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    cANTalonLeftDiciple = RobotMap::subDrivebaseCANTalonLeftDiciple;
    cANTalonRightDiciple = RobotMap::subDrivebaseCANTalonRightDiciple;
}

void SubDrivebase::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new CmdJoystickDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void SubDrivebase::TakeJoystickInputs( std::shared_ptr<Joystick> joystick ) {
	dRV->ArcadeDrive( joystick->GetY(), -joystick->GetX() );
}

void SubDrivebase::Drive(){
	dRV->Drive(0.5, 0);
}

void SubDrivebase::Stop(){
	dRV->Drive(0,0);
}
