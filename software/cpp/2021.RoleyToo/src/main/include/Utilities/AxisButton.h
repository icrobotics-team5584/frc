/*
 * AxisButton.h
 *
 *  Created on: 14 Apr. 2018
 *      Author: Liam
 *
 * 	Updated 20190204_2325 Darcy
 *  Updated 20191204_1954 Mitch
 *  Updated 20210131_1521 Liam
 */

#pragma once
#include <frc/GenericHID.h>
#include <frc2/command/button/Button.h>

class AxisButton : public frc2::Button {
 public:
  explicit AxisButton(frc::GenericHID* joystick, int axisNumber,
                      int deadZone = 0.01)
      : Button([joystick, axisNumber, deadZone] {
          return joystick->GetRawAxis(axisNumber) > deadZone;
        }) {}
};