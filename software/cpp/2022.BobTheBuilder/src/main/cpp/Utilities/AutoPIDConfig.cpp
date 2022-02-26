// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Utilities/AutoPIDConfig.h"

//One
PIDAutoConfig autoRoutineOneLegOne = {
    0, //   double startX;
    0.5, //   double startY;
    0, //   double endX;
    1.5, //   double endY;
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
    0.5, //   double startY;
    0, //   double endX;
    -0.5, //   double endY;
    180, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig autoRoutineOneLegThree = {
    0, //   double startX;
    0.5, //   double startY;
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
    8.34, //   double startX;
    1.383, //   double startY;
    7.550, //   double endX;
    0.563, //   double endY;
    -92, //   double endHeading;
    7.52, //   double cenX;
    3.625, //   double cenY;
    PIDk{3, 0, 30}, //   PIDk PIDconstants;
    1, //   double speed;
    1, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP2 = {
    7.55, //   double startX;
    0.563, //   double startY;
    5.356, //   double endX;
    1.49, //   double endY;
    -44, //   double endHeading;
    7.55, //   double cenX;
    3.625, //   double cenY;
    PIDk{3, 0, 30}, //   PIDk PIDconstants;
    1, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP3 = {
    5.356, //   double startX;
    1.49, //   double startY;
    1.63, //   double endX;
    1.198, //   double endY;
    -99, //   double endHeading;
    5.356, //   double cenX;
    -22.38, //   double cenY;
    PIDk{3, 0, 30}, //   PIDk PIDconstants;
    1, //   double speed;
    0, //   double endSpeed;
    PIDk{1, 0, 9} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP4 = {
    1.63, //   double startX;
    1.198, //   double startY;
    4.571, //   double endX;
    2.498, //   double endY;
    66, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 30}, //   PIDk PIDconstants;
    1, //   double speed;
    0, //   double endSpeed;
    PIDk{1, 0, 9} //   PIDk pidSpeed;
};












