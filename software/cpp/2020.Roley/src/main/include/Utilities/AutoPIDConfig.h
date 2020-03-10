#pragma once
//creates a PIDAutoConfig structure
struct PIDAutoConfig {
    double P;
    double I;
    double D;
    double speed;
    double targetX;
    double targetY;
    double targetYstop;
    double targetAngle;
    double targetAoA;
};

//Declares all the instances of the PIDAutoConfig structure
//(each instance is a different set of PID settings)
extern PIDAutoConfig autoRoutineOneLegOne, autoRoutineOneLegTwo, autoRoutineOneLegThree, autoRoutineOneLegFour, autoRoutineOneLegFive, autoRoutineOneLegSix, 
                     autoRoutineTwoLegOne, autoRoutineTwoLegTwo, autoRoutineTwoLegThree, autoRoutineTwoLegFour, autoRoutineTwoLegFive, autoRoutineTwoLegSix,
                     autoRoutineThreeLegOne, autoRoutineThreeLegTwo, autoRoutineThreeLegThree;
  