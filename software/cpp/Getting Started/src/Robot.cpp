#include "WPILib.h"

class Robot: public IterativeRobot
{

	CANTalon* mFrontLeftDrive = new CANTalon(1);
	CANTalon* mRearLeftDrive = new CANTalon(2);
	CANTalon* mFrontRightDrive = new CANTalon(3);
	CANTalon* mRearRightDrive = new CANTalon(4);

	RobotDrive myRobot; // (a) robot drive system
	Joystick stick;     // (b) only joystick
	LiveWindow *lw;     // (c)
	int autoLoopCounter;

public:
	Robot() :
        // these must be initialized in the same order as they are declared above ...
		myRobot(mFrontLeftDrive, mRearLeftDrive, mFrontRightDrive, mRearRightDrive), // (a)
		stick(0),		                                                             // (b)
		lw(LiveWindow::GetInstance()),                                               // (c)
		autoLoopCounter(0)
	{
		myRobot.SetExpiration(0.1);
	}

private:
	void AutonomousInit()
	{
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			} else {
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
