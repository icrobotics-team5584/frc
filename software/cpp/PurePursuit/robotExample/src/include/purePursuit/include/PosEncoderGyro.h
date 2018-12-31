#pragma once

#include "PositionSource.hpp"
#include <WPILib.h>
using namespace std;

class PosEncoderGyro : public PositionSource {
   public:
    PosEncoderGyro();
    Point get();
private:
    Point currentPoint;
    double prevDistance = 0;
    Timer timer;
};