#pragma once

#include "Utilities/Position.h"

using namespace std;

class PositionSource {
public:    
    virtual Position getPosition() = 0;
    virtual double getAngle() = 0;
    virtual void setPosition(double x, double y) = 0;
};