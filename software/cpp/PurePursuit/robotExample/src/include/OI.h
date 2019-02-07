#pragma once

#include <WPILib.h>

using namespace std;

/*
 * OI holds mappings of controller inputs to commands. If the driver wants
 * to change button assignments, this should be the only place that changes
 * need to be made.
 */

class OI {
private:
  shared_ptr<Joystick> controller;

public:
  OI();
  shared_ptr<Joystick> getController();



};
