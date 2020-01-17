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
    void reset();
    void updatePosition();

private:
    Position currentPosition;
    double prevDistance = 0;
};