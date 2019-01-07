#pragma once

#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"
#include "Position.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

class PathFollower {
public:
    PathFollower(string csvPath, shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output);
    int getPathSize();
    void setLookaheadDistance(double meters);
    void setPointRadius(double meters);
    void followPath();
    bool isFinished();
    void reset();

private:
    double lookaheadDistance = 1;   // Measured in meters
    double pointRadius = 0.3;       // Measured in meters
    vector<Point> path;
    shared_ptr<PositionSource> _source;
    shared_ptr<DriveOutput> _output;

    Position currentPosition;
    int closestPointIndex = 0;
    int xyPathPointCount = -1;

    Point findClosestPoint();
    int findClosestPointIndex();
    double distanceToPoint(double xPoint, double yPoint);
    bool isLookaheadPoint(double x1, double y1, double x2, double y2, double r1, double r2);
    Point findLookaheadPoint();
    double generateDriveCurve();
    double generateSignedCurve();
    void updatePosition();
    int getSign(double);
    vector<Point> constructVectorPath(string csvPath);    
};