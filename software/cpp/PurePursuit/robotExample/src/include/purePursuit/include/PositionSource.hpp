#pragma once

#include <utility>

using namespace std;

class PositionSource {
public:    
    virtual pair<double, double> get() = 0;
};