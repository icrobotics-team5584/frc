#include "OI.h"

OI::OI() {
  controller.reset(new Joystick(0));
}

shared_ptr<Joystick> OI::getController() {
  return controller;
}
