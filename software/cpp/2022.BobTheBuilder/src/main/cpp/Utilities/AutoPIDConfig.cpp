// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/AutoPIDConfig.h"

//One
PIDAutoConfig autoRoutineOneLegOne = {
    0, //   double startX;
    0.5, //   double startY;
    0, //   double endX;
    1.484, //   double endY;
    0, //   double endHeading;
    0, //   double cenX;
    0, //   dou ble cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig autoRoutineOneLegTwo = {
    0, //   double startX;
    1.484, //   double startY;
    0, //   double endX;
    0.2, //   double endY;
    0, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 3}, //   PIDk PIDconstants;
    -0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig autoRoutineOneLegThree = {
    0, //   double startX;
    0, //   double startY;
    0, //   double endX;
    2, //   double endY;
    180, //   double endHeading;
    0, //   double cenX;
    0, //   dou ble cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    -0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP1 = {
    7.46, //   double startX;
    1.86, //   double startY;
    7.557, //   double endX;
    0.379, //   double endY;
    176, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP2 = {
    7.557, //   double startX;
    0.379, //   double startY;
    7.46, //   double endX;
    1.86, //   double endY;
    176, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    -0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP3 = {
    7.557, //   double startX;
    0.878, //   double startY;
    5.041, //   double endX;
    1.872, //   double endY;
    -90, //   double endHeading;
    5.041, //   double cenX;
    -1.727, //   double cenY;
    PIDk{3, 0, 3}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{3, 0, 9} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP4 = {
    5.041, //   double startX;
    1.622, //   double startY;
    1.541, //   double endX;
    1.282, //   double endY;
    -109, //   double endHeading;
    4.001, //   double cenX;
    -5.851, //   double cenY;
    PIDk{3, 0, 3}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{3, 0, 9} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP5 = {
    0, //   double startX;
    0.698, //   double startY;
    5.465, //   double endX;
    2.951, //   double endY;
    67-180, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 3}, //   PIDk PIDconstants;
    -0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{3, 0, 9} //   PIDk pidSpeed;
};












