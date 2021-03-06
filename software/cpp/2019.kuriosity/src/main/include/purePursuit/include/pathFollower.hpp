#pragma once

#include "Point.hpp"
#include "PositionSource.hpp"
#include "DriveOutput.hpp"
#include "Position.h"
#include <vector>
#include <string>
#include <memory>
#include <pathfinder.h>
#include <fstream>
#include "Robot.h"


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
    double getRightSpeedVoltage();
    double getLeftSpeedVoltage();

private:
    double lookaheadDistance = 1.414213562;   // Measured in meters
    double pointRadius = 0.1;       // Measured in meters
    vector<Point> path;
    shared_ptr<PositionSource> _source;
    shared_ptr<DriveOutput> _output;
    std::ofstream velocityFile;
    std::ofstream curveFile;
    Position currentPosition;
    int closestPointIndex = 0;
    int xyPathPointCount = -1;
    const double TRACK_WIDTH = 0.75; //distance between wheels in meters
    double lastRightSpeed = 0;
    double lastLeftSpeed = 0;

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
    double findDistance(double x1, double y1, double x2, double y2);
    vector<Point> constructVectorPathCSV(string csvPath);   
    vector<Point> constructVectorPathSeg(Segment * seg, int pathLength); //Segment is the trajectory that pathfinder returns
    DriveOutput::MotorVelocities generateWheelVelocities(double driveCurve, double targetVelocity);                                                                    //Length is the number of points in the segment                   
};