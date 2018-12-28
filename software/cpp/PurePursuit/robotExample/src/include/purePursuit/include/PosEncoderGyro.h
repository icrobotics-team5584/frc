#pragma once

#include "PositionSource.hpp"
using namespace std;

class PosEncoderGyro : public PositionSource {
   public:
    PosEncoderGyro();
    bool ping();
    Point get();
private:
    Point prevPoint;
    double prevDistance = 0;
};