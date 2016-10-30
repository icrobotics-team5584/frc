package org.usfirst.frc.team5584.robot;

import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Robot extends IterativeRobot {
	RobotDrive myRobot;
	Joystick stick;
	int autoLoopCounter;
	
	CANTalon mFrontLeftDrive = new CANTalon(1);
	CANTalon mRearLeftDrive = new CANTalon(2);
	
	CANTalon mFrontRightDrive = new CANTalon(3);
	CANTalon mRearRightDrive = new CANTalon(4);
	
    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
    	myRobot = new RobotDrive(mFrontLeftDrive,mRearLeftDrive,mFrontRightDrive,mRearRightDrive);
    	stick = new Joystick(0);
    	myRobot.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, false);
    	myRobot.setInvertedMotor(RobotDrive.MotorType.kFrontRight, false);
    	myRobot.setInvertedMotor(RobotDrive.MotorType.kRearLeft, false);
    	myRobot.setInvertedMotor(RobotDrive.MotorType.kRearRight, false);
    }
    
    /**
     * This function is run once each time the robot enters autonomous mode
     */
    public void autonomousInit() {
    	autoLoopCounter = 0;
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {
    	if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.drive(-0.5, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			} else {
			myRobot.drive(0.0, 0.0); 	// stop robot
		}
    }
    
    /**
     * This function is called once each time the robot enters tele-operated mode
     */
    public void teleopInit(){
    }

    /**
     * This function is called periodically during operator control
     */
    public void teleopPeriodic() {
        myRobot.arcadeDrive(stick);
    }
    
    /**
     * This function is called periodically during test mode
     */
    public void testPeriodic() {
    	LiveWindow.run();
    }
    
}
