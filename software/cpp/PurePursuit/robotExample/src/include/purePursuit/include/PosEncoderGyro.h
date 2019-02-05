#pragma once

#include "PositionSource.hpp"
#include "purePursuit/include/Position.h"
#include <WPILib.h>
using namespace std;

class PosEncoderGyro : public PositionSource {
public:
    PosEncoderGyro();
    Position getPosition();
    double getAngle();
    void setPosition(double x, double y);
    void reset();

private:
    Position currentPosition;
    double prevDistance = 0;
};