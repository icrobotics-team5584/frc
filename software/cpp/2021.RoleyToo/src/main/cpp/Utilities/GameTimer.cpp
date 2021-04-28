/*
 * GameTimer.cpp
 *
 *  Created on: 25th March. 2021
 *      Author: Mitch
 */

#include "Utilities/GameTimer.h"
#include <iostream>
#include <math.h>
#include <frc/smartdashboard/SmartDashboard.h>

// TODO: Add tolerance to GameTimer if you're really bored

using namespace std;

GameTimer *GameTimer::_instance = 0;

GameTimer *GameTimer::GetInstance() {
    if (!_instance) {
        _instance = new GameTimer;
    }
    return _instance;
}

GameTimer::LocalTime::LocalTime(int defaultTime) {
    _timeMS = defaultTime;
}
int GameTimer::LocalTime::Seconds() {
    if (_timeMS == -1) {
        return _timeMS;
    }
    else {
        return _timeMS/1000;
    }
}
int GameTimer::LocalTime::Miliseconds() {
    return _timeMS;
}

void GameTimer::LocalTime::SetTime(int timeMS) {
    _timeMS = timeMS;
}

GameTimer::GameTimer() {
    frc::SmartDashboard::PutBoolean("OverrideFMSTime", false);
    frc::SmartDashboard::PutNumber("FMS Time Approximate", 0);
    frc::SmartDashboard::PutNumber("FMS Time Override", 0);
}



int GameTimer::GetTime(TimeUnits timeUnits) {
    switch (timeUnits) {
        case Miliseconds:
            return localTime.Miliseconds();
        case Seconds:
            return localTime.Seconds();
    }
    return -1;
}

void GameTimer::UpdateTime() {

    if (frc::SmartDashboard::GetBoolean("OverrideFMSTime", false)) {
        localTime.SetTime( round(frc::SmartDashboard::GetNumber("FMS Time Override", 0)*1000) );
        frc::SmartDashboard::PutNumber("FMS Time Approximate", localTime.Seconds());
    }
    else {
        localTime.SetTime( round(frc::DriverStation::GetInstance().GetMatchTime()*1000) );
        frc::SmartDashboard::PutNumber("FMS Time Approximate", localTime.Seconds());
    }

}