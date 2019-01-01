#pragma once

#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"
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

private:
    vector<Point> path;
    double lookaheadDistance = 0.8;   // Measured in meters
    double pointRadius = 0.1;  // Measured in meters
    shared_ptr<PositionSource> _source;
    shared_ptr<DriveOutput> _output;
    pair<double, double> currentPosition;

    int closestVelocityPointCount = 0;
    int xyPathPointCount = -1;
    bool pointNotFound = false;

    Point findClosestPoint(double xPos, double yPos, std::vector<Point> xyPath);
    double distanceToPoint(double xPos, double yPos, double xPoint, double yPoint);
    bool isLookaheadPoint(double x1, double y1, double x2, double y2, double r1, double r2);
    Point findLookaheadPoint(double xPos, double yPos, std::vector<Point> xyPath);
    double generateDriveCurve();
    void updatePosition();
    vector<Point> constructVectorPath(string csvPath);    
};