/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CmdHabRoutine.h"
#include "commands/CmdArmToHab.h"
#include "commands/CmdVacuum.h"
#include "commands/CmdArmToFloor.h"
#include "Robot.h"
#include "commands/CmdArmToPreHab.h"

CmdHabRoutine::CmdHabRoutine() {
AddSequential(new CmdArmToHab(), 3.0); 
AddSequential(new CmdVacuum(), 3.0);
AddSequential(new CmdArmToFloor());
}

//void CmdHabRoutine::Initialize() {
    //double difference;
    //const int LessThan = 5;
    //difference = CmdArmToPreHab::angle - Robot::subEncodedArm->getAngle();
//
    //if(difference > LessThan){
    //    this->_Cancel();
    //}
        
//}