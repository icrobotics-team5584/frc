#pragma once

#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"
#include "Position.h"
#include <vector>
#include <string>
#include <memory>
#include <pathfinder.h>

using namespace std;

class PathFollower {
public:
    PathFollower(string csvPath, shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output);
    PathFollower(Segment *seg, int pathLength, shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output);    
    void printPathHead();        
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

    void ImplimentRobotFunctions(shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output);
    Point findClosestPoint();
    int findClosestPointIndex();
    double distanceToPoint(double xPoint, double yPoint);
    bool isLookaheadPoint(double x1, double y1, double x2, double y2, double r1, double r2);
    Point findLookaheadPoint();
    double generateDriveCurve();
    double generateSignedCurve();
    void updatePosition();
    int getSign(double side);
    vector<Point> constructVectorPathCSV(string csvPath);   
    vector<Point> constructVectorPathSeg(Segment * seg, int pathLength); //Segment is the trajectory that pathfinder returns
                                                                         //Length is the number of points in the segment                   
};