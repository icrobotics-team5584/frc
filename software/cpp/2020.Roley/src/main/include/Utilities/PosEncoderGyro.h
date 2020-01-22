#pragma once

#include "PositionSource.hpp"
#include "Utilities/Position.h"

using namespace std;
class PosEncoderGyro {
public:
    PosEncoderGyro();
    double getPositionX();
    double getPositionY();
    double getAngle();
    void setPosition(double x, double y);

    double getTempPositionX();
    double getTempPositionY();
    void setTempPosition(double x, double y);
    void setTempAngle(double tAngle);

    void setInitialAngle(double angle);
    void reset();
    void updateAbsolutePosition();
    void updateRelativePosition();

private:
    Position currentPosition;
    Position tempPosition;
    double prevDistance = 0;
    double prevTDistance = 0;
    double initialAngleOffset = 0;
};