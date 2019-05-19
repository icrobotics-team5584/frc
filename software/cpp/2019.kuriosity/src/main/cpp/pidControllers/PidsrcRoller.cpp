#include "pidControllers/PidsrcRoller.h"
#include "Robot.h"

PidsrcRoller::PidsrcRoller() {}

double PidsrcRoller::PIDGet() {
    return Robot::subRollerIntakeBar->GetAngle();
}
