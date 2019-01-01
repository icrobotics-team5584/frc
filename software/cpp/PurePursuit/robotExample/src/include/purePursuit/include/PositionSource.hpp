#pragma once

#include <utility>

using namespace std;

class PositionSource {
public:    
    virtual pair<double, double> get() = 0;
    virtual void set(double x, double y) = 0;
};