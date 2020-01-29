#include "Utilities/AutoPIDConfig.h"

//Reminder: Update Values when robot lengths are confirmed

/*----------------------------Routine One Setup--------------------*/
//One
PIDAutoConfig autoRoutineOneLegOne = {
  -0.9,     //P
  0.00001,  //I
  -42,      //D
  -0.8,     //speed
  -1.7,     //targetX
  4.537,    //targetY
  0,        //targetAngle
  90        //targetAoA
};
//Two
PIDAutoConfig autoRoutineOneLegTwo = {
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
PIDAutoConfig autoRoutineOneLegThree = {
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
PIDAutoConfig autoRoutineOneLegFour = {
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
/*----------------------------Routine Three Setup------------------*/
/*----------------------------Routine Four Setup-------------------*/