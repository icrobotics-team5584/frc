/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SwitchButtonSceduler.h"

SwitchButtonSceduler::SwitchButtonSceduler(bool last, Trigger* button, Command* orders1, Command* orders2) 
                         : ButtonScheduler(last, button, orders1) {
    secondaryCommand = orders2;
}

SwitchButtonSceduler::Execute(){
    bool pressed = m_button->Grab();
    if (!m_pressedLast && pressed) {
        if (m_command->IsRunning()) {
            m_command->Cancel();
            secondaryCommand->Start();
        } else {
            secondaryCommand->Cancel();
            m_command->Start();
        }
  }

  m_pressedLast = pressed;
}