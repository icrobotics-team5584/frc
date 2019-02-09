#include "pidControllers/PidoutRoller.h"
#include "Robot.h"

PidoutRoller::PidoutRoller() {}

void PidoutRoller::PIDWrite(double output) {
    Robot::subRollerIntakeBar->MoveBar(output);
}