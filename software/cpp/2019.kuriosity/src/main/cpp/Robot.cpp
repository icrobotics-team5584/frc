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
//#include <StringRef.h>

unique_ptr<OI> Robot::_oi;
unique_ptr<RobotMap> Robot::_robotMap;
unique_ptr<SubDriveBase> Robot::subDriveBase;
unique_ptr<SubElevator> Robot::subElevator;
unique_ptr<SubElevatorLimits> Robot::subElevatorLimits;
unique_ptr<SubPanelAffector> Robot::subPanelAffector;
unique_ptr<SubIntakeOutake> Robot::subIntakeOutake;
unique_ptr<SubRollerIntake> Robot::subRollerIntake;
unique_ptr<SubRollerIntakeBar> Robot::subRollerIntakeBar;
unique_ptr<SubGimble> Robot::subGimble;
unique_ptr<SubGimbleLimits> Robot::subGimbleLimits;

void Robot::RobotInit() {
  _robotMap.reset(new RobotMap);

    subDriveBase.reset(new SubDriveBase());
    subElevator.reset(new SubElevator());
    subElevatorLimits.reset(new SubElevatorLimits());
    subIntakeOutake.reset(new SubIntakeOutake());
    subPanelAffector.reset(new SubPanelAffector());
    subRollerIntake.reset(new SubRollerIntake());
    subRollerIntakeBar.reset(new SubRollerIntakeBar());
    subGimble.reset(new SubGimble());
    subGimbleLimits.reset(new SubGimbleLimits());

    // create image processing thread and pass in reference to each variable
    // that we need the thread to provide back to the main robot thread
    std::thread visionThread(Robot::VisionThread, std::ref(Robot::vti_mode), std::ref(Robot::vto_valid), std::ref(Robot::vto_error) );
    visionThread.detach();

    _oi.reset(new OI);
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
    //SmartDashboard::PutNumber("Bottom Ultrasonic", subDriveBase->getDistanceToObstical());
    //SmartDashboard::PutBoolean("front sensor", subDriveBase->frontHasReachedLine());
    //SmartDashboard::PutBoolean("mid sensor", subDriveBase->midHasReachedLine());
    //SmartDashboard::PutBoolean("left sensor", subDriveBase->isLeftClsOnLine());
    //SmartDashboard::PutBoolean("right sensor", subDriveBase->isRightClsOnLine());

    SmartDashboard::PutBoolean("2222222 GIMBLE LIMIT LEFT", subGimbleLimits->GetLeftLimit());
    SmartDashboard::PutBoolean("2222222 GIMBLE LIMIT RIGHT", subGimbleLimits->GetRightLimit());
    
    SmartDashboard::PutNumber("Yaw", subDriveBase->getYaw());
    SmartDashboard::PutNumber("Elevator encoder", subElevator->GetEncoderPosition());
    SmartDashboard::PutBoolean("On Line", subDriveBase->clsBackRightDetected());
    SmartDashboard::PutNumber("Roller bar position", subRollerIntakeBar->GetAngle());
    SmartDashboard::PutNumber("Elevator pos", subElevator->GetEncoderPosition());
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

void Robot::VisionThread( int &mode, bool &valid, double &error ) {

    //cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
    cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera( "10.55.84.11" );

    camera.SetResolution(320, 240);
    camera.SetFPS(20);
    cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
    cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("GripPipeline", 320, 240);
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
        // here the robot code is no longer crashing! This probably redundant if we are
        // now using an IP based AXIS camera.
        if(! source.empty()) {
            framecounter++;

            // STEP 1: process the image
            ic_pipeline.Process(source);

            // STEP 2: fetch references to intermediate pipeline data
            //cv::Mat* img_rgbthreshold = ic_pipeline.GetRgbThresholdOutput();
            cv::Mat* img_desaturate = ic_pipeline.GetDesaturateOutput();
            cv::Mat* img_resizeimage = ic_pipeline.GetResizeImageOutput();
            std::vector<grip::Line>* img_filterlines = ic_pipeline.GetFilterLinesOutput();

            // STEP 3: construct image to display filetered lines
            cv::Mat img_lines = cv::Mat::zeros( img_resizeimage->size(), CV_8UC3 );
            int img_width = img_resizeimage->size().width;
            int img_height = img_resizeimage->size().height;
            // for( size_t i = 0; i< img_filterlines->size(); i++ )
            for( grip::Line line: *img_filterlines )
            {
                cv::Point a;
                a.x = line.x1;
                a.y = line.y1;
                cv::Point b;
                b.x = line.x2;
                b.y = line.y2;
                cv::Scalar colour = cv::Scalar( 0, 255, 255 );
                cv::line(img_lines, a, b, colour, 1);
            }

            // STEP 4: fetch filtered lines and further analyse
            cout << "INFO: searching for longest line" << endl;
            double longest_line_length = 0;
            int lines_found = 0;
            int longest_line_index = -1;
            int longest_line_midx = img_width / 2;
            int longest_line_midy = img_height / 2;
            int i = 0;
            for( grip::Line line: *img_filterlines )
            {
                lines_found++;
                double lineLength = line.length();
                cout << i << ":" << lineLength << endl;
                if(lineLength>longest_line_length)
                {
                    longest_line_length = lineLength;
                    longest_line_index = i;
                    longest_line_midx = line.MidX;
                    longest_line_midy = line.MidY;
                }
                i++;
            }
            cout << "INFO: longest line details:" << endl;
            cout << "  index: " << longest_line_index << endl;
            cout << "  length: " << longest_line_length << endl;
            cout << "  midpoint: (" << longest_line_midx << "," << longest_line_midy << ")" << endl;

            // STEP 6: add midpoint of longest line to display
            if( lines_found > 0 )
              {
                    cv::Point center;
                    center.x = longest_line_midx;
                    center.y = longest_line_midy;
                    cv::Scalar colour = cv::Scalar( 255, 0, 0 );
                    cv::circle(img_lines, center, 5, colour, 2, 8);
              }

            // STEP 6: output one stream to dashboard
            // outputStreamStd.PutFrame( *img_resizeimage );
            // outputStreamStd.PutFrame( *img_rgbthreshold );
            outputStreamStd.PutFrame( img_lines );

            // STEP 7: save images
            // THIS IS NOT WORKING YET
            // string imagepath = "/home/lvuser/field.images/field." + to_string(framecounter) + ".png";
            // imwrite( imagepath.c_str(), *img_resizeimage, compression_params );

            // STEP 8: update target error for use by turret, calculate a value between -1 and +1
            // where -1 is far left of FOV,; +1 is far right of FOV and 0 is centerline
            if( lines_found > 0 )
            {
                error = ( 1.0 * longest_line_midx - (img_width/2) ) / (img_width/2);
                valid = 1;
            } else {
                error = 0;
                valid = 0;
            }

        } else {
            error = 0;
            valid = 0;
        }
        std::cout << "INFO: frame count: " << framecounter << std::endl;
        std::cout << "INFO: mode:" << mode << std::endl;
        std::cout << "INFO: valid: " << valid << std::endl;
        std::cout << "INFO: error: " << error << std::endl;
    }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
