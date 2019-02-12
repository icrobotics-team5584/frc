/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include <cameraserver/CameraServer.h>
#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <gripPipeline/GripPipeline.h>

unique_ptr<OI> Robot::_oi;
unique_ptr<RobotMap> Robot::_robotMap;
unique_ptr<SubDriveBase> Robot::subDriveBase;
unique_ptr<SubElevator> Robot::subElevator;
unique_ptr<SubElevatorLimits> Robot::subElevatorLimits;
unique_ptr<SubPanelAffector> Robot::subPanelAffector;
unique_ptr<SubIntakeOutake> Robot::subIntakeOutake;
unique_ptr<SubRollerIntake> Robot::subRollerIntake;
unique_ptr<SubGimble> Robot::subGimble;

void Robot::RobotInit() {
  _robotMap.reset(new RobotMap);

    subDriveBase.reset(new SubDriveBase());
    subElevator.reset(new SubElevator());
    subElevatorLimits.reset(new SubElevatorLimits());
    subIntakeOutake.reset(new SubIntakeOutake());
    subPanelAffector.reset(new SubPanelAffector());
    subRollerIntake.reset(new SubRollerIntake());
    subGimble.reset(new SubGimble());

    std::thread visionThread(VisionThread);
    visionThread.detach();

    _oi.reset(new OI);
    std::cout << "robot init finish" << std::endl;

    SmartDashboard::PutBoolean("started running End()", false);
    SmartDashboard::PutBoolean("started running backwards()", false);
    SmartDashboard::PutBoolean("finished running backwards()", false);

    // m_chooser.SetDefaultOption("Default Auto", &m_defaultAuto);
    // m_chooser.AddOption("My Auto", &m_myAuto);
    // frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
    SmartDashboard::PutNumber("Bottom Ultrasonic", subDriveBase->getDistanceToObstical());
    SmartDashboard::PutNumber("Yaw", subDriveBase->getYaw());
    SmartDashboard::PutNumber("Elevator encoder", subElevator->GetEncoderPosition());
    SmartDashboard::PutBoolean("On Line", subDriveBase->clsBackRightDetected());
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {


    // std::string autoSelected = frc::SmartDashboard::GetString(
    //     "Auto Selector", "Default");
    // if (autoSelected == "My Auto") {
    //   m_autonomousCommand = &m_myAuto;
    // } else {
    //   m_autonomousCommand = &m_defaultAuto;
    // }

    // m_autonomousCommand = m_chooser.GetSelected();

    //  if (m_autonomousCommand != nullptr) {
    //   m_autonomousCommand->Start();
    // }
}

void Robot::AutonomousPeriodic() {

}

void Robot::TeleopInit() {
    Robot::subElevator->SetHeight(BOTTOM_HATCH);
    subDriveBase->resetYaw();

}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TestPeriodic() {}

void Robot::VisionThread() {
    cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
    camera.SetResolution(320, 240);
    camera.SetFPS(20);
    cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
    cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
    cv::Mat source;
    int framecounter = 0;
    vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    //Setup image pipeline
    grip::GripPipeline ic_pipeline;

    while(true) {
        cvSink.GrabFrame(source);
        // We check for null image here to prevent assertion faults causing robot code to
        // crash. This appears to be caused by the USB subsystem not detecting the camera.
        // If the frame count displayed in the console at run time is not increasing then
        // this indicates that USB camera is not providing frames - you seem to need to
        // restart the roborio to resolve this problem - at least with this empty check 
        // here the robot code is no longer crashing!
        if(! source.empty()) {
            framecounter++;

            // process the image
            ic_pipeline.Process(source);

            // fetch the pre-processed image and display
            cv::Mat* img_rgbthreshold = ic_pipeline.GetRgbThresholdOutput();
            outputStreamStd.PutFrame( *img_rgbthreshold );

            // fetch filtered lines and further analyse
            // (TBA)
            std::vector<grip::Line>* img_filterlines = ic_pipeline.GetFilterLinesOutput();
            cout << "INFO: searching for longest line" << endl;
            double longest_line_length = 0;
            int longest_line_index = -1;
//            for( size_t i = 0; i< img_filterlines->size(); i++ ) // iterate through each line.
            int i = 0;
            for( grip::Line line: *img_filterlines )
            {
                double lineLength = line.length();
                cout << i << ":" << lineLength << endl;
                if(lineLength>longest_line_length)
                {
                    longest_line_length = lineLength;
                    longest_line_index = i;
                }
                i++;
            }
            cout << "INFO: Index of longest line" << endl;
            cout << longest_line_index << " (" << longest_line_length << ")" << endl;

            // fetch resized image to file for analysis during practice matches
            cv::Mat* img_resizeimage = ic_pipeline.GetResizeImageOutput();
            string imagepath = "/run/field." + to_string(framecounter) + ".png";
            imwrite( imagepath.c_str(), *img_resizeimage, compression_params );
        }
        std::cout << "INFO: frame count: " << framecounter << std::endl;
    }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
