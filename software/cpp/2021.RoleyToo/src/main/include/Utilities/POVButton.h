/*
 *  POVButton.h
 *
 *  Created on: 20190102
 *  	Author: Darcy Meago
 * 	
 *  Updated 20210131_1622
 */

#pragma once
#include <frc/GenericHID.h>
#include <frc2/command/button/Button.h>

class POVButton : public frc2::Button {
 public:
  enum class Position {
    up = 0,
    upright = 45,
    right = 90,
    downright = 135,
    down = 180,
    downleft = 225,
    left = 270,
    upleft = 315,
  };

  explicit POVButton(frc::GenericHID* joystick, Position position)
      : Button([joystick, position] {
          return joystick->GetPOV() == static_cast<int>(position);
        }) {}
};
