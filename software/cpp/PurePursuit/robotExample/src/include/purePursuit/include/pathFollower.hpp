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

public:
    vector<Point> constructVectorPath(string csvPath);    
    PathFollower(string csvPath, PositionSource source, DriveOutput output);
    PathFollower();
    void setLookAheadDistance(double meters);
    void followPath();
    bool isFinished();

    ~PathFollower();
};