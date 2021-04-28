/*
 * GameTimer.cpp
 *
 *  Created on: 25th March. 2021
 *      Author: Mitch
 */

#pragma once

#include <frc/DriverStation.h>

class GameTimer {
 public: 
  static GameTimer* GetInstance();
  enum TimeUnits {
    Miliseconds,
    Seconds
  };

  int GetTime(TimeUnits timeUnits);
  void UpdateTime();
 private:
  GameTimer();
  class LocalTime {
   public:
     LocalTime(int defaultTime);
     int Seconds();
     int Miliseconds();
     void SetTime(int timeMS);
   private:
     int _timeMS;
   };
  LocalTime localTime{-1};
  frc::DriverStation* _driverStation;
  static GameTimer* _instance;
};
