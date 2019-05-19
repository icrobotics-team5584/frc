#include "pidControllers/PidsrcEncoderDrive.h"
#include "Robot.h"

PidsrcEncoderDrive::PidsrcEncoderDrive() {}

double PidsrcEncoderDrive::PIDGet() {
    //frc::SmartDashboard::PutNumber("distance travelled", Robot::subDriveBase->getDistanceTravelled());
    return Robot::subDriveBase->getDistanceTravelled();
}
