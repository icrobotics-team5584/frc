#include "Utilities/AutoPIDConfig.h"

//Reminder: Update Values when robot lengths are confirmed

/*----------------------------Routine One Setup--------------------*/
//One
PIDAutoConfig autoRoutineOneLegOne = {
  0.7,     //P
  0.0,  //I
  25,      //D
  0.6,     //speed
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
  -0.6,      //speed
  0,        //targetX
  0,   //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineOneLegThree = {
  -0.7,     //P
  0.0,  //I
  -25,      //D
  -0.6,     //speed
  -1.7,     //targetX
  2.2,    //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineOneLegFour = {
  -0.7,        //P
  0.0,     //I
  -25,       //D
  -0.6,      //speed
  -1.7,        //targetX
  5.1,   //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
PIDAutoConfig autoRoutineOneLegFive = {
  0.7,      //P
  0, //I
  25,       //D
  0.6,      //speed
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
  0.6,      //speed
  0,        //targetX
  -2,    //targetY
  -2.048, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
};
/*----------------------------Routine Two Setup--------------------*/
PIDAutoConfig autoRoutineTwoLegOne = {
  0.65,     //P
  0.0,  //I
  29,      //D
  0.4,     //speed
  0,     //targetX
  -0.3,    //targetY
  -2.148, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
  
};
//Two
PIDAutoConfig autoRoutineTwoLegTwo = {
  0.65,     //P
  0.0,  //I
  29,      //D
  0.4,     //speed
  1.7,     //targetX
  -2.148,    //targetY
  -2.151, //target y turn around point
  0,        //targetAngle
  15,        //targetAoA
};
PIDAutoConfig autoRoutineTwoLegThree = {
  -0.65,     //P
  0.0,  //I
  -29,      //D
  -0.4,     //speed
  1.7,     //targetX
  -1.848,
  5.1, //target y turn around point
  0,        //targetAngle
  10,        //targetAoA
  
};
//Two
PIDAutoConfig autoRoutineTwoLegFour = {
  -0.65,     //P
  0.0,  //I
  -29,      //D
  -0.4,     //speed
  0,     //targetX
  0,    //targetY
  5.1, //target y turn around point
  0,        //targetAngle
  15,        //targetAoA
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
  -0.9,     //P
  0.00001,  //I
  -42,      //D
  -0.8,     //speed
  0,     //targetX
  3.3,    //targetY
  3.3, //target y turn around point
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