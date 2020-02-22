/*----------------------------------------------------------------------------*/
/* RobotMap.h                                                                 */
/*----------------------------------------------------------------------------*/

#pragma once
enum Can {
    can_srxShooterLeft = 5,
    can_srxShooterRight = 6,
    can_srxIntake = 7,
    can_srxStorage = 8, 
    can_srxClimberRight = 9,
    can_srxClimberLeft =  10,
};

enum PCM_ID{
    pcm_0 = 0,
    pcm_1 = 1,
};

enum PCM_0{
    pcm_solIntakeDeploy = 0,
    pcm_solIntakeRetract = 1,
    pcm_solDollyDeploy = 2,
    pcm_solDollyRetract = 3,
    pcm_solStorageForward = 4,
    pcm_solStorageRetract = 5,
    pcm_buddyIn = 6,
    pcm_buddyOut = 7,
};

enum PCM_1{
    pcm_solRatchetEngage = 0,
    pcm_solRatchetDisengage = 1,
};

enum PWM{
    pwn_Storage = 0,
};

enum DIO{
    dio_ElevatorBottom = 2,
    dio_ElevatorTop = 3,
};

enum SPM{
    SPM_DriveBaseFrontLeft = 1,
    SPM_DriveBaseBackLeft = 2,
    SPM_DriveBaseFrontRight = 3,
    SPM_DriveBaseBackRight = 4,
    SPM_StorageBottom = 6,
};

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
