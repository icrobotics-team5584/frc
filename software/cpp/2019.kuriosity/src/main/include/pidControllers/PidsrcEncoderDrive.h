#pragma once

#include <frc/WPILib.h>

class PidsrcEncoderDrive : public frc::PIDSource {
public:
    PidsrcEncoderDrive();
    double PIDGet();
};