// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/AutoPIDConfig.h"

//One
PIDAutoConfig autoRoutineOneLegOne = {
    0, //   double startX;
    0.5, //   double startY;
    0, //   double endX;
    2.5, //   double endY;
    0, //   double endHeading;
    0, //   double cenX;
    0, //   dou ble cenY;
    PIDk{-1, 0, 0}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{1, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig autoRoutineOneLegTwo = {
    0, //   double startX;
    2, //   double startY;
    1, //   double endX;
    1, //   double endY;
    90, //   double endHeading;
    1, //   double cenX;
    2, //   double cenY;
    PIDk{1, 0, 0}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP1 = {
    0, //   double startX;
    2, //   double startY;
    1, //   double endX;
    1, //   double endY;
    90, //   double endHeading;
    1, //   double cenX;
    2, //   double cenY;
    PIDk{1, 0, 0}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP2 = {
    0, //   double startX;
    2, //   double startY;
    1, //   double endX;
    1, //   double endY;
    90, //   double endHeading;
    1, //   double cenX;
    2, //   double cenY;
    PIDk{1, 0, 0}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP3 = {
    0.5, //   double startX;
    0, //   double startY;
    5, //   double endX;
    0, //   double endY;
    90, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 30}, //   PIDk PIDconstants;
    1, //   double speed;
    0, //   double endSpeed;
    PIDk{1, 0, 9} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP4 = {
    4, //   double startX;
    0, //   double startY;
    -0.5, //   double endX;
    0, //   double endY;
    -90, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 30}, //   PIDk PIDconstants;
    1, //   double speed;
    0, //   double endSpeed;
    PIDk{1, 0, 9} //   PIDk pidSpeed;
};












