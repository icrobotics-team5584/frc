#pragma once

#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class PathFollower {
private:
    vector<Point> path;
    double lookAheadDistance;   //Measured in meters
    shared_ptr<PositionSource> _source;
    shared_ptr<DriveOutput> _output;
    Point currentPoint;

    Point findClosestPoint();
    Point findLookaheadPoint();
    double generateDriveCurve();
    void updatePosition();
    void driveCurve();
    vector<Point> constructVectorPath(string csvPath);    

public:
    PathFollower(string csvPath, shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output);
    int getPathSize();
    Point getCurrentPoint();
    void setLookAheadDistance(double meters);
    void followPath();
    bool isFinished();

    ~PathFollower();
};