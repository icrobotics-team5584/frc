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
    1.9, //   double endY;
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
    PIDk{-3, 0, -12}, //   PIDk PIDconstants;
    0.9, //   double speed;
    0, //   double endSpeed;
    PIDk{1.5, 0, 8} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP2 = {
    7.524, //   double startX;
    0.878, //   double startY;
    6.325, //   double endX;
    1.479, //   double endY;
    53, //   double endHeading;
    //-127,
    6.774, //   double cenX;
    0.878, //   double cenY;
    PIDk{3, 0, 12}, //   PIDk PIDconstants;
    -0.9, //   double speed;
    -0.9, //   double endSpeed;
    PIDk{-1.5, 0, -8} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP3 = {
    6.325, //   double startX;
    1.479, //   double startY;
    4.059, //   double endX;
    1.182, //   double endY;
    112, //   double endHeading;
    4.928, //   double cenX;
    3.348, //   double cenY;
    PIDk{-3, 0, -12}, //   PIDk PIDconstants;
    -0.9, //   double speed;
    0, //   double endSpeed;
    PIDk{-1.5, 0, -8} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP4 = {
    4.223, //   double startX;
    1.297, //   double startY;
    5.041, //   double endX;
    1.872, //   double endY;
    55, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{1, 0, 12}, //   PIDk PIDconstants;
    0.9, //   double speed;
    0, //   double endSpeed;
    PIDk{1.5, 0, 8} //   PIDk pidSpeed;
};
//end 3 ball
PIDAutoConfig auto5BallP5 = {
    4.632, //   double startX;
    1.584, //   double startY;
    1.272, //   double endX;
    1.13, //   double endY;
    -98, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 12}, //   PIDk PIDconstants;
    0.9, //   double speed;
    0, //   double endSpeed;
    PIDk{1.5, 0, 8} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP6 = {
    1.569, //   double startX;
    1.17, //   double startY;
    4.664, //   double endX;
    1.479, //   double endY;
    66, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 12}, //   PIDk PIDconstants;
    0.9, //   double speed;
    0, //   double endSpeed;
    PIDk{1.5, 0, 8} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP7 = {
    1.379, //   double startX;
    1.395, //   double startY;
    2.209, //   double endX;
    1.912, //   double endY;
    -110, //   double endHeading;
    3.03, //   double cenX;
    -0.33, //   double cenY;
    PIDk{-3, 0, -12}, //   PIDk PIDconstants;
    -0.9, //   double speed;
    -0.9, //   double endSpeed;
    PIDk{-1.5, 0, -8} //   PIDk pidSpeed;
};

PIDAutoConfig auto5BallP8 = {
    2.209, //   double startX;
    1.912, //   double startY;
    4.569, //   double endX;
    2.775, //   double endY;
    -110, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{3, 0, 12}, //   PIDk PIDconstants;
    -0.9, //   double speed;
    0, //   double endSpeed;
    PIDk{-1.5, 0, -8} //   PIDk pidSpeed;
};


PIDAutoConfig auto3BallP1 = {
    7.46, //   double startX;
    1.86, //   double startY;
    7.557, //   double endX;
    0.379, //   double endY;
    176, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    0.5, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 2} //   PIDk pidSpeed;
};

PIDAutoConfig auto3BallP2 = {
    7.524, //   double startX;
    0.878, //   double startY;
    6.325, //   double endX;
    1.479, //   double endY;
    53, //   double endHeading;
    //-127,
    6.774, //   double cenX;
    0.878, //   double cenY;
    PIDk{3, 0, 3}, //   PIDk PIDconstants;
    -0.5, //   double speed;
    -0.5, //   double endSpeed;
    PIDk{-2, 0, -2} //   PIDk pidSpeed;
};

PIDAutoConfig auto3BallP3 = {
    6.325, //   double startX;
    1.479, //   double startY;
    4.059, //   double endX;
    1.182, //   double endY;
    112, //   double endHeading;
    4.928, //   double cenX;
    3.348, //   double cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    -0.5, //   double speed;
    0, //   double endSpeed;
    PIDk{-2, 0, -2} //   PIDk pidSpeed;
};

PIDAutoConfig auto3BallP4 = {
    4.223, //   double startX;
    1.297, //   double startY;
    5.141, //   double endX;
    1.672, //   double endY;
    68, //   double endHeading;
    0, //   double cenX;
    0, //   double cenY;
    PIDk{-3, 0, -3}, //   PIDk PIDconstants;
    0.2, //   double speed;
    0, //   double endSpeed;
    PIDk{2, 0, 0} //   PIDk pidSpeed;
};











