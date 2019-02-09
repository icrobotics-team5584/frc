#pragma once

#include <frc/WPILib.h>

class PidsrcRoller : public frc::PIDSource {
public:
    PidsrcRoller();
    double PIDGet();
};