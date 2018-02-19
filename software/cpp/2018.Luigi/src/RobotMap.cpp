#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"
#include "WPILib.h"

//Define DriveBase Actuators
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleft;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXright;
std::shared_ptr<frc::DifferentialDrive> RobotMap::subDriveBaseDifferentialDrive;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXleftSlave;
std::shared_ptr<WPI_TalonSRX> RobotMap::subDriveBaseSRXrightSlave;

//Define Intake Actuators and Sensors
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxRight;
std::shared_ptr<WPI_TalonSRX> RobotMap::subIntakeTnxLeft;
std::shared_ptr<VictorSP> RobotMap::subIntakeSpFinger;
std::shared_ptr<DigitalInput> RobotMap::subIntakeSwtFingerUp;
std::shared_ptr<DigitalInput> RobotMap::subIntakeSwtRightLimit;
std::shared_ptr<DigitalInput> RobotMap::subIntakeSwtLeftLimit;

//Define Ultrasonic sensors Analog
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputFront;
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputRight;
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputBack;
//std::shared_ptr<frc::AnalogInput> RobotMap::subDriveBaseUltrasonicInputLeft;

//Define Ultrasonic sensors Echo
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputFront;
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputRight;
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputBack;
std::shared_ptr<frc::Ultrasonic> RobotMap::subDriveBaseUltrasonicInputLeft;

//Define arm lift Actuators / Actuator
std::shared_ptr<WPI_TalonSRX> RobotMap::subEncodedArmLiftSrxMaster;
std::shared_ptr<WPI_TalonSRX> RobotMap::subEncodedArmLiftSrxSlave;
std::shared_ptr<DigitalInput> RobotMap::subEncodedArmLiftSwtTop;
std::shared_ptr<DigitalInput> RobotMap::subEncodedArmLiftSwtTopSecondary;
std::shared_ptr<DigitalInput> RobotMap::subEncodedArmLiftSwtBottom;

//Define Ramp drop actuator
std::shared_ptr<VictorSP> RobotMap::subRampSPLeft;

void RobotMap::init() {

	//Initiate DriveBase Actuators
		//Masters:
		subDriveBaseSRXleft.reset(new WPI_TalonSRX(1));
		subDriveBaseSRXright.reset(new WPI_TalonSRX(3));
			//Reset Sensor positions to zero for future profiles
			RobotMap::subDriveBaseSRXright->SetSelectedSensorPosition(0, 0, 10);
			RobotMap::subDriveBaseSRXleft->SetSelectedSensorPosition(0, 0, 10);
		//Slaves:
		subDriveBaseSRXleftSlave.reset(new WPI_TalonSRX(2));
		subDriveBaseSRXleftSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 1);
		subDriveBaseSRXrightSlave.reset(new WPI_TalonSRX(4));
		subDriveBaseSRXrightSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 3);
		//Differential Drive:
		subDriveBaseDifferentialDrive.reset(new frc::DifferentialDrive(*subDriveBaseSRXleft, *subDriveBaseSRXright));
		subDriveBaseDifferentialDrive->SetSafetyEnabled(false);
		subDriveBaseDifferentialDrive->SetExpiration(0.1);
		subDriveBaseDifferentialDrive->SetMaxOutput(1.0);
		// Setup encoders on master drive motors for position control:
		subDriveBaseSRXleft->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
		subDriveBaseSRXright->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
		subDriveBaseSRXleft->ConfigNeutralDeadband(0.001, 10);
		subDriveBaseSRXright->ConfigNeutralDeadband(0.001, 10);
		subDriveBaseSRXleft->ConfigMotionProfileTrajectoryPeriod(0, 10);
		subDriveBaseSRXright->ConfigMotionProfileTrajectoryPeriod(0, 10);
		subDriveBaseSRXleft->SetSensorPhase(true);
		subDriveBaseSRXright->SetSensorPhase(true);
		// Setup FPID parameters for master drive motors:
		double LeftFgain = 0.181434;    double RightFgain = 0.180678;
		double LeftPgain = 2.0;      double RightPgain = 2.0;
		double LeftIgain = 0.0;      double RightIgain = 0.0;
		double LeftDgain = 20.0;     double RightDgain = 20.0;
		subDriveBaseSRXleft->SelectProfileSlot(0, 0);
		subDriveBaseSRXleft->Config_kF(0, LeftFgain, 10);
		subDriveBaseSRXleft->Config_kP(0, LeftPgain, 10);
		subDriveBaseSRXleft->Config_kI(0, LeftIgain, 10);
		subDriveBaseSRXleft->Config_kD(0, LeftDgain, 10);
		subDriveBaseSRXright->SelectProfileSlot(0, 0);
		subDriveBaseSRXright->Config_kF(0, RightFgain, 10);
		subDriveBaseSRXright->Config_kP(0, RightPgain, 10);
		subDriveBaseSRXright->Config_kI(0, RightIgain, 10);
		subDriveBaseSRXright->Config_kD(0, RightDgain, 10);

	//Initiate Intake Actuators
    subIntakeTnxLeft.reset(new WPI_TalonSRX(7));
    subIntakeTnxRight.reset(new WPI_TalonSRX(8));
    subIntakeSpFinger.reset(new VictorSP(1));

    //Initiate Intake Sensors
    subIntakeSwtFingerUp.reset(new DigitalInput(6));
    subIntakeSwtLeftLimit.reset(new DigitalInput(0));
    subIntakeSwtRightLimit.reset(new DigitalInput(1));

//    //Initiate Ultrasonic sensors Analog
//    subDriveBaseUltrasonicInputFront.reset(new frc::AnalogInput(0));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputFront);
//    subDriveBaseUltrasonicInputRight.reset(new frc::AnalogInput(1));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputRight);
//    subDriveBaseUltrasonicInputBack.reset(new frc::AnalogInput(2));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputBack);
//    subDriveBaseUltrasonicInputLeft.reset(new frc::AnalogInput(3));
//    	//lw->AddSensor("SubUltrasonic", "UltrasonicInputFront",  subDriveBaseUltrasonicInputLeft);

    //initiate echo Ultrasonic objects
    subDriveBaseUltrasonicInputFront.reset(new frc::Ultrasonic(11,13));
    subDriveBaseUltrasonicInputRight.reset(new frc::Ultrasonic(15,17));
    subDriveBaseUltrasonicInputBack.reset(new frc::Ultrasonic(19,21));
    subDriveBaseUltrasonicInputLeft.reset(new frc::Ultrasonic(23,25));

    //Construct Motion Profiles
//    mpBaseline.reset(new MotionProfileData(kBaselineA, kBaselineB, kBaselineASz));
//    mpTest.reset(new MotionProfileData(kMPLtest, kMPRtest, kMPLtestSz));

    //Initiate Ramp Drop Actuator
    subRampSPLeft.reset(new VictorSP(0));

    //Initiate arm lift Actuators / Actuator /Sensors
    subEncodedArmLiftSrxMaster.reset(new WPI_TalonSRX(5));
    subEncodedArmLiftSrxSlave.reset(new WPI_TalonSRX(6));
    subEncodedArmLiftSrxSlave->Set( ctre::phoenix::motorcontrol::ControlMode::Follower, 5);
    subEncodedArmLiftSwtTop.reset(new DigitalInput(3));
    subEncodedArmLiftSwtTopSecondary.reset(new DigitalInput(4));
    subEncodedArmLiftSwtBottom.reset(new DigitalInput(2));

    enum Constants
    {
    	/**
    	 * Which PID slot to pull gains from.  Starting 2018, you can choose
    	 * from 0,1,2 or 3.  Only the first two (0,1) are visible in web-based configuration.
    	 */
    	 kSlotIdx = 0,

    	/* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
    	 * For now we just want the primary one.
    	 */
    	 kPIDLoopIdx = 0,

    	/*
    	 * set to zero to skip waiting for confirmation, set to nonzero to wait
    	 * and report to DS if action fails.
    	 */
    	 kTimeoutMs = 10
    };

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	int absolutePosition = subEncodedArmLiftSrxMaster->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
		/* use the low level API to set the quad encoder signal */
	subEncodedArmLiftSrxMaster->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);

	/* choose the sensor and sensor direction */
	subEncodedArmLiftSrxMaster->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
	subEncodedArmLiftSrxMaster->SetSensorPhase(false);

	/* set the peak and nominal outputs, 12V means full */
	subEncodedArmLiftSrxMaster->ConfigNominalOutputForward(0, kTimeoutMs);
	subEncodedArmLiftSrxMaster->ConfigNominalOutputReverse(0, kTimeoutMs);
	subEncodedArmLiftSrxMaster->ConfigPeakOutputForward(1, kTimeoutMs);
	subEncodedArmLiftSrxMaster->ConfigPeakOutputReverse(-1, kTimeoutMs);

	/* set closed loop gains in slot0 */
	subEncodedArmLiftSrxMaster->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
	subEncodedArmLiftSrxMaster->Config_kP(kPIDLoopIdx, 0.4, kTimeoutMs);
	subEncodedArmLiftSrxMaster->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	subEncodedArmLiftSrxMaster->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

}
