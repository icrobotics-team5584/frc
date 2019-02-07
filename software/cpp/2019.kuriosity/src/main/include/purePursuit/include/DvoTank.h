#pragma once

#include "DriveOutput.hpp"

class DvoTank : public DriveOutput {
    void set(MotorVelocities motorVelocities);
};