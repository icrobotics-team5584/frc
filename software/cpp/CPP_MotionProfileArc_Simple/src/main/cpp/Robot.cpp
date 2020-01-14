#include "Robot.h"
#include "MotionProfile.h"
#include "Instrum.h"
#
void Robot::RobotInit() 
{
    /* Construct global variables */

    // DIZZY MOTOR CONTROLLERS:
    // _rightMaster = new TalonSRX(1);
    // _leftMaster = new TalonSRX(3);
    // _rightMaster->ConfigFactoryDefault();
    // _leftMaster->ConfigFactoryDefault();
    // MUCK MOTOR CONTROLLERS:
    _rightMaster = new TalonSRX(12);
    _leftMaster = new TalonSRX(11);
    _rightMaster->ConfigFactoryDefault();
    _leftMaster->ConfigFactoryDefault();

    // DIZZY MOTOR CONTROLLERS:
    // _rightSlave = new TalonSRX(2);
    // _leftSlave = new TalonSRX(4);
    // _rightSlave->ConfigFactoryDefault();
    // _leftSlave->ConfigFactoryDefault();
    // MUCK MOTOR CONTROLLERS:
    _rightSlave = new VictorSPX(13);
    _leftSlave = new VictorSPX(10);
    _rightSlave->ConfigFactoryDefault();
    _leftSlave->ConfigFactoryDefault();

    // DIZZY CONTROLLER PAIRING:
    // _rightSlave->Set(ControlMode::Follower, 1);
    // _leftSlave->Set(ControlMode::Follower, 3);
    // MUCK CONTROLLER PAIRING:
    // _rightSlave->Set(ControlMode::Follower, 12); OR ...
    _rightSlave->Follow(*_rightMaster);
    // _leftSlave->Set(ControlMode::Follower, 11); OR ...
    _leftSlave->Follow(*_leftMaster);

    // DIZZY PIDGEON CONTROLLER:
    // _pidgeyNest = new TalonSRX(7);
    // _pidgeyNest->ConfigFactoryDefault();
    // MUCK PIDGEON CONTROLLER:
    _pidgeyNest = new TalonSRX(30);
    _pidgeyNest->ConfigFactoryDefault();

    // _pidgey = new PigeonIMU(3); //This uses a CAN pigeon, as opposed to a gadgeteer pigeon
    _pidgey = new PigeonIMU(_pidgeyNest); //This uses a gadgeteer pigeon

    _joystick = new frc::Joystick(0);
    _bufferedStream = new BufferedTrajectoryPointStream();

    _plotThread = new PlotThread(_rightMaster);

    /* Initialize buffer with motion profile */
    InitBuffer(kMotionProfile, kMotionProfileSz, 1.0); //Do a full (1.0) rotation to the left
//    InitBuffer(kMotionProfile, kMotionProfileSz, 0.5); //Do a half (0.5) rotation to the left
//    InitBuffer(kMotionProfile, kMotionProfileSz, 0.25); //Do a quarter (0.25) rotation to the left
//    InitBuffer(kMotionProfile, kMotionProfileSz, 0.0); //No rotation
    _state = 0;


    _masterConfig = new MasterProfileConfiguration(_leftMaster, _pidgeyNest, _pidgey);
    _followConfig = new FollowerProfileConfiguration();

    _rightMaster->ConfigAllSettings(*_masterConfig);
    _leftMaster->ConfigAllSettings(*_followConfig);

    // note that sensor phase needs to be set here so that SensorSum
    // increases by approximately 8192u when we push the robot forward
    _rightMaster->SetSensorPhase(false);
    _leftMaster->SetSensorPhase(false);

    // if need be, invert one or other side of robot
    _rightMaster->SetInverted(false);
    _leftMaster->SetInverted(true);

    // these should be set to the same as masters
    _rightSlave->SetInverted(false);
    _leftSlave->SetInverted(true);

    // set these to sensible value here so that we can see whats going
    // on when we manually push robot around during setup
    _rightMaster->GetSensorCollection().SetQuadraturePosition(0);
    _leftMaster->GetSensorCollection().SetQuadraturePosition(0);

    _rightMaster->SetStatusFramePeriod(StatusFrameEnhanced::Status_14_Turn_PIDF1, 20); //Telemetry using Phoenix Tuner
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() 
{
    /* get joystick button and stick */
    bool bPrintValues = _joystick->GetRawButton(2);
    bool bFireMp = _joystick->GetRawButton(1);
    double axis = -_joystick->GetRawAxis(1);
    double turn = _joystick->GetRawAxis(0);

    /* if button is up, just drive the motor in PercentOutput */
    if (bFireMp == false) {
        _state = 0;
    }

    switch (_state) {
        /* drive master talon normally */
        case 0:
            _rightMaster->Set(ControlMode::PercentOutput, axis, DemandType_ArbitraryFeedForward, -turn);
            _leftMaster->Set(ControlMode::PercentOutput, axis, DemandType_ArbitraryFeedForward, turn);

            if (bFireMp == true) {
                /* go to MP logic */
                _state = 1;
            }
            break;

        /* fire the MP, and stop calling set() since that will cancel the MP */
        case 1:
            _rightMaster->GetSensorCollection().SetQuadraturePosition(0);
            _leftMaster->GetSensorCollection().SetQuadraturePosition(0);
            _pidgey->SetYaw(0);
            /* wait for 10 points to buffer in firmware, then transition to MP */
            _leftMaster->Follow(*_rightMaster, FollowerType_AuxOutput1);
            int mperr;
            mperr = _rightMaster->StartMotionProfile(*_bufferedStream, 45, ControlMode::MotionProfileArc);
            _state = 2;
            Instrum::PrintLine("MP started");
            std::cout << "mperr : " << mperr << std::endl;
            bPrintValues = true;
            break;

        /* wait for MP to finish */
        case 2:
            bPrintValues = true;
            if (_rightMaster->IsMotionProfileFinished()) {
                bPrintValues = false;
                Instrum::PrintLine("MP finished");
                _state = 3;
            }
            break;

        /* MP is finished, hand control back to joystick */
        case 3:
            break;
    }

    /* print MP values */
    Instrum::Loop(bPrintValues, _rightMaster);
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::InitBuffer(const double profile[][4], int totalCnt, double rotations)
{
    bool forward = true; // set to false to drive in opposite direction of profile (not really needed
                         // since you can use negative numbers in profile).

    TrajectoryPoint point; // temp for for loop, since unused params are initialized
                           // automatically, you can alloc just one

    /* clear the buffer, in case it was used elsewhere */
    _bufferedStream->Clear();

    // double turnAmount = rotations * 8192.0; //8192 units per rotation for a pigeon

    /* Insert every point into buffer, no limit on size */
    for (int i = 0; i < totalCnt; ++i) {

        double direction = forward ? +1 : -1;
        double positionRot = profile[i][0];
        double velocityRPM = profile[i][1];
        double headingDeg = profile[i][2];
        int durationMilliseconds = (int) profile[i][3];

        /* for each point, fill our structure and pass it to API */
        point.timeDur = durationMilliseconds;
        point.position = direction * positionRot * 4096; // Convert Revolutions to
                                                         // Units
        point.velocity = direction * velocityRPM * 4096 / 600.0; // Convert RPM to
                                                                 // Units/100ms
        
        /** 
         * Here is where you specify the heading of the robot at each point. 
         * In this example we're linearly interpolating creating a segment of a circle to follow
         */
        point.auxiliaryPos = ( headingDeg / 360.0 ) * 8192.0; //8192 units per rotation for a pigeon
        
        point.auxiliaryVel = 0;
        
        point.profileSlotSelect0 = 0; /* which set of gains would you like to use [0,3]? */
        point.profileSlotSelect1 = 1; /* which set of gains would you like to use [0,3]? */
        point.zeroPos = (i == 0); /* set this to true on the first point */
        point.isLastPoint = ((i + 1) == totalCnt); /* set this to true on the last point */
        point.arbFeedFwd = 0; /* you can add a constant offset to add to PID[0] output here */

        point.useAuxPID = true; /* Using auxiliary PID */
        _bufferedStream->Write(point);
    }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
