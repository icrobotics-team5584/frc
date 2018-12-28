#pragma once

#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"
#include <vector>
#include <string>

using namespace std;

class PathFollower {
private:
    vector<Point> path;
    double lookAheadDistance;   //Measured in meters
    PositionSource positionSource;
    DriveOutput driveOutput;

    Point findClosestPoint();
    Point findLookaheadPoint();
    double generateDriveCurve();
    void updatePosition();
    void driveCurve();
    vector<Point> constructVectorPath(string csvPath);    

public:
    PathFollower(string csvPath, PositionSource* source, DriveOutput* output);
    int getPathSize();
    void setLookAheadDistance(double meters);
    void followPath();
    bool isFinished();

    ~PathFollower();
};