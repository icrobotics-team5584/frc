/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <vector>
#include "purePursuit/include/Point.hpp"
#include "purePursuit/include/pathFollower.hpp"


using namespace std;

class CmdMakePath : public frc::Command {
   private:
    vector<Point> path;
    unique_ptr<PathFollower> pathFollower;

   public:
    CmdMakePath();
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;
};
