#include "pidControllers/PidsrcEncoderDrive.h"
#include "Robot.h"

PidsrcEncoderDrive::PidsrcEncoderDrive() {}

double PidsrcEncoderDrive::PIDGet() {
    return Robot::subDriveBase->getDistanceTravelled();
}
