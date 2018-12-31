#include "purePursuit/include/pathFollower.hpp"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

/*
 * Instantiate a PathFollower object with a given robot path represented by a
 * csv file of x, y, velocity points. source is the object used to determine
 * robot's current position, and output is the object used to operate the
 * drivebase. During construction, this class prints the size and first five
 * points of the created path.
 */
PathFollower::PathFollower(string csvPath, shared_ptr<PositionSource> source,
                           shared_ptr<DriveOutput> output) {
    // Save objects locally
    _source = source;
    _output = output;
    path = constructVectorPath(csvPath);

    // Output debug information
    cout << "path of size " << getPathSize() << " created." << endl;
    cout << "first points:" << endl;
    for (int i = 0; i < min(getPathSize(), 5); i++) {
        cout << "  " << path[i].x << path[i].y << path[i].velocity << endl;
    }
}

Point PathFollower::findClosestPoint() {
    Point p;
    p.velocity = 0;
    p.x = 0;
    p.y = 0;
    return p;
}

Point PathFollower::findLookaheadPoint() {
    Point p;
    p.velocity = 0;
    p.x = 0;
    p.y = 0;
    return p;
}

double PathFollower::generateDriveCurve() { return 0; }

void PathFollower::updatePosition() {}

void PathFollower::driveCurve() {}

void PathFollower::setLookAheadDistance(double meters) {}

// Run this in execute, presumed to run every 20ms
void PathFollower::followPath() { 
    currentPoint = _source->get();
}

bool PathFollower::isFinished() { return true; }

// This functions takes a csv file with an x and y header, and puts it all into
// pairs (doubles) and then into a vector to make it easy to read.
std::vector<Point> PathFollower::constructVectorPath(string csvPath) {
    // open the file
    cout << "Constructing path: " << csvPath << endl;
    std::ifstream data("home/lvuser/paths/" + csvPath + ".csv");
    std::string line;
    std::vector<Point> xyPath;
    std::string x, y, v;
    // go through each line of the csv file, grab the x and y value, and put it
    // into a pair, and then into a vector.
    while (std::getline(data, line)) {
        std::stringstream ss(line);
        std::getline(ss, x, ',');
        std::getline(ss, y, ',');
        std::getline(ss, v, ',');  // velocity
        // convert the strings from the csv to doubles so that our program can
        // use them
        double pointX = ::atof(x.c_str());
        double pointY = ::atof(y.c_str());
        double velocity = ::atof(v.c_str());
        Point point;
        point.x = pointX;
        point.y = pointY;
        point.velocity = velocity;
        xyPath.push_back(point);
        // cout for debugging in the future
        //      std::cout << "x: " << point.x << " | y: " << point.y << " |
        //      velcoity: " << point.velocity << std::endl;
    }
    return xyPath;
}

Point PathFollower::getCurrentPoint() { 
    return currentPoint; 
}

int PathFollower::getPathSize() { return path.size(); }

PathFollower::~PathFollower() {}