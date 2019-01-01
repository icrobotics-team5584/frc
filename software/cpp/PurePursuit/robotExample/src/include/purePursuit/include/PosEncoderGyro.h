#pragma once

#include "PositionSource.hpp"
#include "purePursuit/include/Point.hpp"
#include <WPILib.h>
using namespace std;

class PosEncoderGyro : public PositionSource {
   public:
    PosEncoderGyro();
    pair<double, double> get();
private:
    pair<double, double> currentPosition;
    double prevDistance = 0;
    Timer timer;
};