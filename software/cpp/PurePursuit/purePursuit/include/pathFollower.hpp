#pragma once

#include <vector>
#include <string>
#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"

using namespace std;

class PathFollower {
private:
    vector<Point> path;
    double lookAheadDistance;   //Measureed in meters
    PositionSource positionSource;
    DriveOutput driveOutput;

    Point findClosestPoint();
    Point findLookaheadPoint();
    double generateDriveCurve();
    void updatePosition();
    vector<Point> constructVectorPath(string csvPath);

public:
    PathFollower(string csvPath, PositionSource source, DriveOutput output);
    void setLookAheadDistacne(double meters);
    void followPath();
    bool isFinished();
};