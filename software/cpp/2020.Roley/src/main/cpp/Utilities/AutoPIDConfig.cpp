#include "Utilities/AutoPIDConfig.h"

//Reminder: Update Values when robot lengths are confirmed

/*----------------------------Routine One Setup--------------------*/
//One
PIDAutoConfig autoRoutineOneLegOne = {
  -0.9,     //P
  0.00001,  //I
  -42,      //D
  -0.8,     //speed
  -1.6,     //targetX
  2.2,    //targetY
  0,        //targetAngle
  90        //targetAoA
};
//Two
PIDAutoConfig autoRoutineOneLegTwo = {
  -3,        //P
  0.0,     //I
  -80,       //D
  -0.6,      //speed
  -1.6,        //targetX
  4.5,   //targetY
  0,        //targetAngle
  90        //targetAoA
};
PIDAutoConfig autoRoutineOneLegThree = {
  0.9,      //P
  -0.00001, //I
  42,       //D
  0.8,      //speed
  -1.6,     //targetX
  2.312,    //targetY
  -22.5,        //targetAngle
  90        //targetAngle of Attack
};
//Three
PIDAutoConfig autoRoutineOneLegFour = {
  0.9,      //P
  -0.00001, //I
  42,       //D
  0.8,      //speed
  0,        //targetX
  0,        //targetY
  0,        //targetAngle
  90        //targetAoA
};
//Four
PIDAutoConfig autoRoutineOneLegFive = {
  3,        //P
  -0.0,     //I
  80,       //D
  0.5,      //speed
  0,        //targetX
  -2.553,   //targetY
  0,        //targetAngle
  90        //targetAoA
};
/*----------------------------Routine Two Setup--------------------*/
PIDAutoConfig autoRoutineTwoLegOne = {
  -3,        //P
  0.0,     //I
  -80,       //D
  -0.6,      //speed
  0,        //targetX
  1.78,   //targetY
  0,        //targetAngle
  90        //targetAoA
};
//Two
PIDAutoConfig autoRoutineTwoLegTwo = {
  0.9,      //P
  -0.00001, //I
  42,       //D
  0.8,      //speed
  -1.7,     //targetX
  2.312,    //targetY
  -22.5,        //targetAngle
  90        //targetAngle of Attack
};
//Three
PIDAutoConfig autoRoutineTwoLegThree = {
  0.9,      //P
  -0.00001, //I
  42,       //D
  0.8,      //speed
  0,        //targetX
  0,        //targetY
  0,        //targetAngle
  90        //targetAoA
};
/*----------------------------Routine Three Setup------------------*/
PIDAutoConfig autoRoutineThreeLegOne = {
  -0.9,     //P
  0.00001,  //I
  -42,      //D
  -0.8,     //speed
  0,     //targetX
  3.3,    //targetY
  0,        //targetAngle
  90        //targetAoA
};
//Two
PIDAutoConfig autoRoutineThreeLegTwo = {
  0.9,      //P
  -0.00001, //I
  42,       //D
  0.8,      //speed
  0,     //targetX
  1,    //targetY
  -22.5,        //targetAngle
  90        //targetAngle of Attack
};
PIDAutoConfig autoRoutineThreeLegThree = {
  3,        //P
  -0.0,     //I
  80,       //D
  0.5,      //speed
  1.6,        //targetX
  -2.553,   //targetY
  0,        //targetAngle
  90        //targetAoA
};

/*----------------------------Routine Four Setup-------------------*/