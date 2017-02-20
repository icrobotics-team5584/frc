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
#include "Commands/CmdAuto2ShootGoals.h"
#include "Commands/CmdAuto3DeployGearFromRight.h"
#include "Commands/CmdAuto4DeployGearFromLeft.h"
#include "Commands/CmdAutoDrive.h"
#include "Commands/CmdAutoDriveToPeg.h"
#include "Commands/CmdAutoTurn.h"
#include "Commands/CmdAutonomous.h"
#include "Commands/CmdChunder.h"
#include "Commands/CmdClimb.h"
#include "Commands/CmdFeedMe.h"
#include "Commands/CmdIntakeDeploy.h"
#include "Commands/CmdIntakeRollerIn.h"
#include "Commands/CmdIntakeRollerOut.h"
#include "Commands/CmdIntakeSliderIn.h"
#include "Commands/CmdIntakeSliderInClimb.h"
#include "Commands/CmdIntakeSliderOut.h"
#include "Commands/CmdJoystickDrive.h"
#include "Commands/CmdLaunchFuel.h"
#include "Commands/CmdLaunchFuelPrime.h"
#include "Commands/CmdMoveServo.h"
#include "Commands/GearFlapIn.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    joystick1.reset(new Joystick(0));
    
    btnGearFlapIn.reset(new JoystickButton(joystick1.get(), 6));
    btnGearFlapIn->WhileHeld(new GearFlapIn());
    btnRolllerIn.reset(new JoystickButton(joystick1.get(), 12));
    btnRolllerIn->WhileHeld(new CmdIntakeRollerIn());
    btnRollerOut.reset(new JoystickButton(joystick1.get(), 11));
    btnRollerOut->WhileHeld(new CmdIntakeRollerOut());
    btnIntakeSliderOut.reset(new JoystickButton(joystick1.get(), 9));
    btnIntakeSliderOut->WhileHeld(new CmdIntakeSliderOut());
    btnIntakeSliderIn.reset(new JoystickButton(joystick1.get(), 10));
    btnIntakeSliderIn->WhileHeld(new CmdIntakeSliderIn());
    btnClimb.reset(new JoystickButton(joystick1.get(), 4));
    btnClimb->WhileHeld(new CmdClimb());
    btnMoveServo.reset(new JoystickButton(joystick1.get(), 8));
    btnMoveServo->WhileHeld(new CmdMoveServo());
    btnIntakeSliderInClimb.reset(new JoystickButton(joystick1.get(), 5));
    btnIntakeSliderInClimb->WhileHeld(new CmdIntakeSliderInClimb());
    btnFuelLaunch.reset(new JoystickButton(joystick1.get(), 1));
    btnFuelLaunch->WhileHeld(new CmdLaunchFuel());
    btnFuelLaunchPrime.reset(new JoystickButton(joystick1.get(), 2));
    btnFuelLaunchPrime->WhileHeld(new CmdLaunchFuelPrime());
    btnIntakeDeployRollerToggle.reset(new JoystickButton(joystick1.get(), 3));
    btnIntakeDeployRollerToggle->WhileHeld(new CmdIntakeDeploy());

    // SmartDashboard Buttons
    SmartDashboard::PutData("CmdAuto4DeployGearFromLeft", new CmdAuto4DeployGearFromLeft());
    SmartDashboard::PutData("CmdAuto3DeployGearFromRight", new CmdAuto3DeployGearFromRight());
    SmartDashboard::PutData("CmdAuto2ShootGoals", new CmdAuto2ShootGoals());
    SmartDashboard::PutData("GearFlapIn", new GearFlapIn());
    SmartDashboard::PutData("CmdIntakeSliderInClimb", new CmdIntakeSliderInClimb());
    SmartDashboard::PutData("CmdIntakeSliderOut", new CmdIntakeSliderOut());
    SmartDashboard::PutData("CmdIntakeSliderIn", new CmdIntakeSliderIn());
    SmartDashboard::PutData("CmdIntakeRollerOut", new CmdIntakeRollerOut());
    SmartDashboard::PutData("CmdIntakeRollerIn", new CmdIntakeRollerIn());
    SmartDashboard::PutData("CmdLaunchFuelPrime", new CmdLaunchFuelPrime());
    SmartDashboard::PutData("CmdAutoDriveToPeg", new CmdAutoDriveToPeg());
    SmartDashboard::PutData("CmdAutoTurn: Nothing", new CmdAutoTurn(0, 0));
    SmartDashboard::PutData("CmdChunder", new CmdChunder());
    SmartDashboard::PutData("CmdFeedMe", new CmdFeedMe());
    SmartDashboard::PutData("CmdIntakeDeploy", new CmdIntakeDeploy());
    SmartDashboard::PutData("CmdAutonomous", new CmdAutonomous());
    SmartDashboard::PutData("CmdAutoDrive: Nothing", new CmdAutoDrive(0, 0, 0));
    SmartDashboard::PutData("CmdLaunchFuel", new CmdLaunchFuel());
    SmartDashboard::PutData("CmdClimb", new CmdClimb());
    SmartDashboard::PutData("CmdMoveServo", new CmdMoveServo());
    SmartDashboard::PutData("CmdJoystickDrive", new CmdJoystickDrive());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getJoystick1() {
   return joystick1;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
