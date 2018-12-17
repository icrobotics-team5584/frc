#include "purePursuit/include/pathFollower.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <stdlib.h>

PathFollower::PathFollower() {
        
}

PathFollower::PathFollower(string csvPath, PositionSource source, DriveOutput output) {}

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

double PathFollower::generateDriveCurve() {
        return 0;
}

void PathFollower::updatePosition() {}

void PathFollower::driveCurve() {}

void PathFollower::setLookAheadDistance(double meters) {
}

void PathFollower::followPath() {}

bool PathFollower::isFinished() {
        return true;
}

// This functions takes a csv file with an x and y header, and puts it all into pairs (doubles) and then into a vector to make it easy to read.
std::vector<Point> PathFollower::constructVectorPath(string csvPath) {
        //open the file
        std::ifstream data(csvPath);
        std::string line;
        std::vector<Point> xyPath;
        std::string x, y, v;
        //go through each line of the csv file, grab the x and y value, and put it into a pair, and then into a vector.
        while(std::getline(data,line)){
                std::stringstream ss(line);
                std::getline(ss, x, ',');
                std::getline(ss, y, ',');
                std::getline(ss, v, ','); //velocity
                //convert the strings from the csv to doubles so that our program can use them
                double pointX = ::atof(x.c_str());
                double pointY = ::atof(y.c_str());
                double velocity = ::atof(v.c_str());
                Point point;
                point.x = pointX;
                point.y = pointY;
                point.velocity = velocity;
                xyPath.push_back(point);
                //cout for debugging in the future
                //      std::cout << "x: " << point.x << " | y: " << point.y << " | velcoity: " << point.velocity << std::endl;

        } 
        return xyPath;
}

PathFollower::~PathFollower(){
        
}