#pragma once

#include <units/length.h>
#include <units/angle.h>
#include <frc/geometry/Translation2d.h>

/*
 * A little namespace with functions to simulate a vision system that gives you the angle to the
 * target and distance from the target. This is not a great simulation since you don't have to be
 * looking at the target to see it.
 */

namespace FakeVision {
units::meter_t GetDistToTarget();
units::degree_t GetAngleToTarget();
static frc::Translation2d goalPosition{(54_ft + 1_in) / 2,
                                (26_ft + 7_in) / 2};  // field size / 2
};  // namespace FakeVision
