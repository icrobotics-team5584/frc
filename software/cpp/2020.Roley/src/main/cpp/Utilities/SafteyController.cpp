#include "Utilities/SafteyController.h"

SafteyController::SafteyController() {}

SafteyController::Direction SafteyController::GetEncoderDirection() {
    // if encoder > prevEncoder
    //  return FORWARD
    // else if encoder < prevEncoder
    //  return BACKWARD
    // else
    //  return IDLE
}

SafteyController::Direction SafteyController::GetMotorDirection() {
    if (GetMotorPower() > 0) {
        return Direction::FORWARD;
    } else if (GetMotorPower() < 0) {
        return Direction::BACKWARD;
    } else {
        return Direction::IDLE;
    }
}

void SafteyController::Periodic() {
    if (GetMotorDirection() != GetEncoderDirection()) {
        //OHSHITSTOP!
    }
    prevEncoderValue = GetEncoderValue();
}
