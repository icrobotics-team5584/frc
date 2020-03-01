#include "Utilities/AutoPIDConfig.h"

//Reminder: Update Values when robot lengths are confirmed

/*----------------------------Routine One Setup--------------------*/
//One
PIDAutoConfig autoRoutineOneLegOne = {
  0.7,     //P
  0.0,  //I
  25,      //D
  0.5,     //speed
  0,     //targetX
  -2,    //targetY
  -2.048, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
//Two
PIDAutoConfig autoRoutineOneLegTwo = {
  -0.7,        //P
  0.0,     //I
  -25,       //D
  -0.5,      //speed
  0,        //targetX
  0,   //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineOneLegThree = {
  -0.7,     //P
  0.0,  //I
  -28,      //D
  -0.5,     //speed
  -1.9,     //targetX
  2.2,    //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineOneLegFour = {
  -0.7,        //P
  0.0,     //I
  -25,       //D
  -0.5,      //speed
  -1.9,        //targetX
  5.1,   //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineOneLegFive = {
  0.7,      //P
  0, //I
  25,       //D
  0.5,      //speed
  -1.6,     //targetX
  2.312,    //targetY
  -2.048,
  -22.5,        //targetAngle
  10,        //targetAngle of Attack
};
PIDAutoConfig autoRoutineOneLegSix = {
  0.7,      //P
  0, //I
  25,       //D
  0.5,      //speed
  -0.2,        //targetX
  -2,    //targetY
  -2.048, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
/*----------------------------Routine Two Setup--------------------*/
PIDAutoConfig autoRoutineTwoLegOne = {
  0.7,      //P
  0, //I
  25,       //D
  0.5,      //speed
  0,     //targetX
  -2.0,    //targetY
  -2.5, //target y turn around point
  -36,        //targetAngle
  10,        //targetAngle of Attack
};
//Two
PIDAutoConfig autoRoutineTwoLegTwo = {
 -0.7,        //P
  0.0,     //I
  -25,       //D
  -0.5,      //speed
  0,        //targetX
  5.1,   //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineTwoLegThree = {
  0.7,        //P
  0.0,     //I
  25,       //D
  0.5,      //speed
  0.1,        //targetX
  0,   //targetY
  -2.5, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
//Two
PIDAutoConfig autoRoutineTwoLegFour = {
 0.7,      //P
  0, //I
  25,       //D
  0.5,      //speed
  0.1,     //targetX
  -1.9,    //targetY
  -2.5, //target y turn around point
  -36,        //targetAngle
  10,        //targetAngle of Attack
};
PIDAutoConfig autoRoutineTwoLegFive = {
  -0.7,        //P
  0.0,     //I
  -25,       //D
  -0.6,      //speed
  0,        //targetX
  5.1,   //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineTwoLegSix = {
  0.7,        //P
  0.0,     //I
  25,       //D
  0.6,      //speed
  0,        //targetX
  0,   //targetY
  -2.150, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
/*----------------------------Routine Three Setup------------------*/
PIDAutoConfig autoRoutineThreeLegOne = {
  -0.7,      //P
  0, //I
  -25,       //D
  -0.2,      //speed
  0,     //targetX
  2.8,    //targetY
  3.5,
  26,        //targetAngle
  90,        //targetAngle of Attack
};
//Two
PIDAutoConfig autoRoutineThreeLegTwo = {
  0.9,      //P
  -0.00001, //I
  42,       //D
  0.8,      //speed
  0,     //targetX
  1,    //targetY
  -2.553, //target y turn around point
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
  -2.553, //target y turn around point
  0,        //targetAngle
  90        //targetAoA
};

/*----------------------------Routine Four Setup-------------------*/