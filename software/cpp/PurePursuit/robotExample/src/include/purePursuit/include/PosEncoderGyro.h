#pragma once

#include "PositionSource.hpp"
#include "purePursuit/include/Point.hpp"
#include <WPILib.h>
using namespace std;

class PosEncoderGyro : public PositionSource {
public:
    PosEncoderGyro();
    void reset();
    pair<double, double> get();
    void set(double x, double y);
private:
    pair<double, double> currentPosition;
    double prevDistance = 0;
};