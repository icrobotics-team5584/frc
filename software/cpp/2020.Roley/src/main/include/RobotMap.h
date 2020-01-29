/*----------------------------------------------------------------------------*/
/* RobotMap.h                                                                 */
/*----------------------------------------------------------------------------*/

#pragma once
enum Can {
    can_srxDriveBaseFrontLeft = 1,
    can_srxDriveBaseBackLeft = 2,
    can_srxDriveBaseFrontRight = 3,
    can_srxDriveBaseBackRight = 4,
    can_srxShooterLeft = 5,
    can_srxShooterRight = 6  
};

enum PCM{
    pcm_solIntakeDeploy = 0,
    pcm_solIntakeRetract = 1,
};

enum PWM{
    pwn_Storage = 0,
};



// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
constexpr int kIntakeMotor = 7;
