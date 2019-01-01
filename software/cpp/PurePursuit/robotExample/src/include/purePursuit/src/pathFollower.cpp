#include "purePursuit/include/pathFollower.hpp"
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>
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

int PathFollower::getPathSize() { return path.size(); }

void PathFollower::setLookaheadDistance(double meters) {
    lookaheadDistance = meters;
}

void PathFollower::setPointRadius(double meters) {
    pointRadius = meters;
}

// Drives the robot along the path as long as this is continuously called. 
void PathFollower::followPath() { 
    currentPosition = _source->get();
}

bool PathFollower::isFinished() { return false; }

/*
 * This function returns the 'closest' point. However, it only works under
 * certain circumstances. It is designed for a path following robot that begins
 * at the START of its csv path. It looks at when its distance to path points
 * begin to increase, and by doing that it knows that the points are becoming
 * further away. Through this technique, we are able to know what our closest
 * point is by telling it that when the distance to points increase, then the
 * last point must be the closest point. This function is used to get the
 * closest point so that the robot's velocity can be set to the velocity of that
 * robot. Giving it a random value will not work. Try to draw this on a paper
 * with the robot about 1cm off the path and a random point that was
 * 'previously' used for finding velocity. Then draw lines between each point
 * and notice how the distance from them increase as you go along the path.
 */
Point PathFollower::findClosestPoint(double xPos, double yPos,
                                     std::vector<Point> xyPath) {
    // a velocity point is just a normal point from the csv, but we are using it
    // for velocity purpose
    Point velocityPoint;
    double oldVelocityPointX, oldVelocityPointY;
    double newVelocityPointX, newVelocityPointY;
    oldVelocityPointX = xyPath.at(closestVelocityPointCount).x;
    oldVelocityPointY = xyPath.at(closestVelocityPointCount).y;
    // so that we can compare the original and the changing distances so that we
    // know when the distance is getting bigger.
    double oldDistance =
        distanceToPoint(xPos, yPos, oldVelocityPointX, oldVelocityPointY);
    double newDistance;
    // so that the loop goes on forever (the return breaks it)
    while (true) {
        closestVelocityPointCount++;
        newVelocityPointX = xyPath.at(closestVelocityPointCount).x;
        newVelocityPointY = xyPath.at(closestVelocityPointCount).y;
        newDistance =
            distanceToPoint(xPos, yPos, newVelocityPointX, newVelocityPointY);
        Point point = xyPath.at(closestVelocityPointCount);
        std::cout << "olddistance: " << oldDistance
                  << "| newdistance: " << newDistance << std::endl;
        // checks whether we are currently looking at our closest point (if it
        // is true then yes)
        if (newDistance > oldDistance) {
            velocityPoint = xyPath.at(closestVelocityPointCount);
            return velocityPoint;
        } else {
            newVelocityPointX = oldVelocityPointX;
            newVelocityPointY = oldVelocityPointY;
        }
    }
}

// Use pythagoras to find the distance between 2 points
double PathFollower::distanceToPoint(double xPos, double yPos, double xPoint,
                                     double yPoint) {
    double distance;
    distance = std::sqrt((xPos - xPoint) * (xPos - xPoint) +
                         (yPos - yPoint) * (yPos - yPoint));
    return distance;
}

/*
 * Creates circle around robot, the lookahead point will be where that circle
 * intersects the path ahead of the current position.
 * If the distance between the two centres is smaller or equal to the sum of
 * the radii it returns true (they intersect) it is squared to avoid using a
 * sqrt (because who likes those amiright)
 */
bool PathFollower::isLookaheadPoint(double x1, double y1, double x2, double y2,
                                    double r1, double r2) {
    double distSq = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    double radSumSq = (r1 + r2) * (r1 + r2);
    // if they distance is greater than the sum of the two triangles, they are
    // not touching
    if (distSq > radSumSq) return false;
    // this checks whether it circle is inside the other
    else if (distSq < std::abs(r1 - r2))
        return false;
    // check whether they are the same circle (will not happen in our current
    // situation, since the radiuses are different, but just in case)
    else if ((distSq == 0) && (r1 = r2))
        return false;
    else if (distSq < radSumSq)
        return true;
    else
        return false;
}

Point PathFollower::findLookaheadPoint(double xPos, double yPos,
                                       std::vector<Point> xyPath) {
    Point pathPoints;
    double xPoint, yPoint;
    // keeps track of where our last point was so that we dont have to search
    // the entire vector for the point again
    bool doTheyIntersect = false;
    // if they intersect, give that point to the program to follow
    while (!doTheyIntersect) {
        xyPathPointCount++;
        xPoint = xyPath.at(xyPathPointCount).x;
        yPoint = xyPath.at(xyPathPointCount).y;
        // if the distance between the two centres of the circles is
        // smaller/equal to the radius, the circles intersect/touch
        doTheyIntersect = isLookaheadPoint(xPoint, yPoint, xPos, yPos,
                                           pointRadius, lookaheadDistance);
        // std::cout << "x: " << xPoint << " y: " << yPoint <<" intecept?" <<
        // doTheyIntersect << std::endl;
    }
    pathPoints.x = xPoint;
    pathPoints.y = yPoint;
    return pathPoints;
}

double PathFollower::generateDriveCurve() { return 0; }

void PathFollower::updatePosition() { currentPosition = _source->get(); }

/*
 * Loads path points from a csv file in the format:
 * x position, y position, velocity
 * x position, y position, velocity
 * etc..
 */
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