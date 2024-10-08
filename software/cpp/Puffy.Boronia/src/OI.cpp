// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/ChuckBoulder.h"
#include "Commands/CollectBoulder.h"
#include "Commands/DriveWithJoysticks.h"
#include "Commands/FeedBoulder.h"
#include "Commands/ForwardFeed.h"
#include "Commands/ForwardIntake.h"
#include "Commands/FrontArmDown.h"
#include "Commands/LowMode.h"
#include "Commands/LowerArmToShoot.h"
#include "Commands/ReverseFeed.h"
#include "Commands/ReverseIntake.h"
#include "Commands/RunShooterMotors.h"
#include "Commands/ShooterArmDown.h"
#include "Commands/ThrowBoulderFeedSequence.h"
#include "Commands/ThrowBoulderIntakeSequence.h"
#include "Commands/ThrowBoulderSequence.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    joystick1.reset(new Joystick(0));
    
    joystickButtonThrowBoulder.reset(new JoystickButton(joystick1.get(), 1));
    joystickButtonThrowBoulder->WhenPressed(new ThrowBoulderSequence());
    joystickButtonLowMode.reset(new JoystickButton(joystick1.get(), 8));
    joystickButtonLowMode->WhileHeld(new LowMode());
    joystickButtonShooterArmDown.reset(new JoystickButton(joystick1.get(), 7));
    joystickButtonShooterArmDown->WhileHeld(new ShooterArmDown());
    joystickButtonFrontArmDown.reset(new JoystickButton(joystick1.get(), 6));
    joystickButtonFrontArmDown->WhileHeld(new FrontArmDown());
    joystickButtonFeed.reset(new JoystickButton(joystick1.get(), 3));
    joystickButtonFeed->WhileHeld(new FeedBoulder());
    joystickButtonPickup.reset(new JoystickButton(joystick1.get(), 5));
    joystickButtonPickup->WhenPressed(new CollectBoulder());
    joystickButtonShoot.reset(new JoystickButton(joystick1.get(), 4));
    joystickButtonShoot->WhileHeld(new ChuckBoulder());

    // SmartDashboard Buttons
    SmartDashboard::PutData("LowerArmToShoot", new LowerArmToShoot());
    SmartDashboard::PutData("ThrowBoulderIntakeSequence", new ThrowBoulderIntakeSequence());
    SmartDashboard::PutData("ThrowBoulderFeedSequence", new ThrowBoulderFeedSequence());
    SmartDashboard::PutData("ForwardIntake", new ForwardIntake());
    SmartDashboard::PutData("ForwardFeed", new ForwardFeed());
    SmartDashboard::PutData("ReverseIntake", new ReverseIntake());
    SmartDashboard::PutData("ReverseFeed: asasa", new ReverseFeed(0));
    SmartDashboard::PutData("ReverseFeed: asadsadas", new ReverseFeed(45));
    SmartDashboard::PutData("RunShooterMotors: blah", new RunShooterMotors(999));
    SmartDashboard::PutData("ThrowBoulderSequence", new ThrowBoulderSequence());
    SmartDashboard::PutData("DriveWithJoysticks", new DriveWithJoysticks());
    SmartDashboard::PutData("ShooterArmDown", new ShooterArmDown());
    SmartDashboard::PutData("FrontArmDown", new FrontArmDown());
    SmartDashboard::PutData("FeedBoulder", new FeedBoulder());
    SmartDashboard::PutData("CollectBoulder", new CollectBoulder());
    SmartDashboard::PutData("ChuckBoulder", new ChuckBoulder());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    SmartDashboard::PutBoolean("Boulder On Board", Robot::pickupRoller->IsSwitchSet() );
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getJoystick1() {
   return joystick1;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
