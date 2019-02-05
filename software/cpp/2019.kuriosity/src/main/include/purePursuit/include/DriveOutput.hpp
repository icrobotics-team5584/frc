#pragma once
#include <utility>
using namespace std;

class DriveOutput {

public:
    typedef pair<double, double> MotorVelocities;  
    virtual void set(MotorVelocities motorVelocities) = 0;
};