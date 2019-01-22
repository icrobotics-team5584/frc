#include "purePursuit/include/pathFollower.hpp"
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <utility>
#include <frc/WPILib.h>

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
    ImplimentRobotFunctions(source, output);
    path = constructVectorPathCSV(csvPath);
    _source->setPosition(path[0].position.x, path[0].position.y);
}

PathFollower::PathFollower(Segment* seg, int pathLength, shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output) {
    ImplimentRobotFunctions(source, output);
    path = constructVectorPathSeg(seg, pathLength);
    _source->setPosition(path[0].position.x, path[0].position.y);
}

void PathFollower::ImplimentRobotFunctions(shared_ptr<PositionSource> source, shared_ptr<DriveOutput> output) {
    _source = source;
    _output = output;
}

void PathFollower::printPathHead() {
    if (getPathSize() > 0) {
        cout << "path of size " << getPathSize() << " created." << endl;
        cout << "first points:" << endl;
        for (int i = 0; i < min(getPathSize(), 5); i++) {
            cout << "  " << path[i].position.x << path[i].position.y << path[i].velocity << endl;
        }
    } else {
        cout << "WARNING: Pure Pursuit path size is zero, this could cause problems. " <<
        "Make sure the correct path is selected and the csv files are on the RIO." << endl;
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
    double driveCurve = generateDriveCurve();
    frc::SmartDashboard::PutNumber("driveCurve", driveCurve);

    //_output->set(driveCurve);
}

bool PathFollower::isFinished() { return false; }

void PathFollower::reset() {
    _source->setPosition(path[0].position.x, path[0].position.y);
}

/*
 * This function returns the 'closest' point. However, it only works under
 * certain circumstances. It is designed for a path following robot that begins
 * at the START of its vector path. It looks at when its distance to path points
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
Point PathFollower::findClosestPoint() {
    // Get previous closest point data to compare against
    double oldClosestPointX = path.at(closestPointIndex).position.x;
    double oldClosestPointY = path.at(closestPointIndex).position.y;
    double oldDistance = distanceToPoint(oldClosestPointX, oldClosestPointY);

    // Create space for potential new closest points data
    double newClosestPointX;
    double newClosestPointY;
    double newDistance;
    
    // Start search a few points back from previous closest to avoid outrunning the robot
    if (closestPointIndex <= 5) {
        closestPointIndex = -1;
    } else {
        closestPointIndex -= 5;
    }

    // Find the closest point
    while (true) {
        // Get data of next point on path
        closestPointIndex++;
        newClosestPointX = path.at(closestPointIndex).position.x;
        newClosestPointY = path.at(closestPointIndex).position.y;
        newDistance = distanceToPoint(newClosestPointX, newClosestPointY);
        
        // check if point is further from robot than previous point
        if (newDistance > oldDistance) {
            // We passed the closest, return previous point
            if (closestPointIndex > 0) {
                closestPointIndex-=1;
            } else {
                closestPointIndex = 0;
            }
            Point closestPoint = path.at(closestPointIndex); 
            frc::SmartDashboard::PutNumberArray("closest point", {closestPoint.position.x, closestPoint.position.y, closestPoint.velocity});
            return closestPoint;

        } else {
            // Distance is still decreasing, continue search
            newClosestPointX = oldClosestPointX;
            newClosestPointY = oldClosestPointY;
        }
    }
}

int PathFollower::findClosestPointIndex() {
    return closestPointIndex;
}

// Use pythagoras to find the distance between 2 points
double PathFollower::distanceToPoint(double xPoint, double yPoint) {
    double distance;
    double xPos = currentPosition.x;
    double yPos = currentPosition.y;
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

    //cout << "point x: " << x1 << ". point y: " << y1 << ". radius: " << pointRadius << endl;
    //cout << "dist   : " << sqrt(distSq) << ". radSum : " << sqrt(radSumSq) << endl;

    // if the distance is greater than the sum of the two triangles, they are
    // not touching
    if (distSq > radSumSq) {
        return false;
    }
    // this checks whether it circle is inside the other
    else if (distSq < std::abs(r1 - r2)) {
        return false;
    }
    // check whether they are the same circle (will not happen in our current
    // situation, since the radiuses are different, but just in case)
    else if ((distSq == 0) && (r1 = r2)) {
        return false;
    }
    else if (distSq < radSumSq) {
        return true;
    }
    else {
        return false;
    }
}

Point PathFollower::findLookaheadPoint() {
    double xPos = currentPosition.x;
    double yPos = currentPosition.y;

    Point pathPoints;
    double xPoint, yPoint;
    double xyPathPointCount = findClosestPointIndex();  // Start search at point closest to robot

    // Find the point with a radius that intersects the circle made by our lookahead distance
    bool doTheyIntersect = false;
    while ((!doTheyIntersect) && (xyPathPointCount < getPathSize()-1)) {
        xyPathPointCount++;
        xPoint = path.at(xyPathPointCount).position.x;
        yPoint = path.at(xyPathPointCount).position.y;
        // if the distance between the two centres of the circles is
        // smaller/equal to the radius, the circles intersect/touch
        doTheyIntersect = isLookaheadPoint(xPoint, yPoint, xPos, yPos,
                                           pointRadius, lookaheadDistance);
    }
    if (doTheyIntersect) {
        pathPoints.position.x = xPoint;
        pathPoints.position.y = yPoint;
    } else {
        cout << "ERROR: Could not find lookahead point. Using 0, 0" << endl;
    }

    frc::SmartDashboard::PutNumberArray("lookahead point", {xPoint, yPoint});
    return pathPoints;
}

/*
 * Generates the curve that the robot needs to drive along to reach its lookahead point. 
 * Note that curvature = 1/radius. This curvature can be given directly to a DifferentialDrive
 * objcet using the CurvatureDrive() function.
 */
double PathFollower::generateDriveCurve() {
    // Determine error between LA point and expected robot position
    double tangent = -tan(_source->getAngle());
    double c = tangent * (currentPosition.x - currentPosition.y); // Details at Team 1712's paper
    Point lookAheadPoint = findLookaheadPoint();
    double error = abs(tangent * lookAheadPoint.position.x +
                       lookAheadPoint.position.y + c) / sqrt(pow(tangent,2) + 1);
                       
    // Determine drive absolute curve (direction to come after)
    double curve = 2 * error / pow(lookaheadDistance, 2);

    // Determine whether to curve left or right 
    double distToLAPoint = 0;
    double distToExpectedRobotPos = 0;

    return 0;
}
double PathFollower::generateSignedCurve() {
    Point lookAheadPoint = findLookaheadPoint();
    Position position = currentPosition;
    double signedCurvature;
    //foward is supposed to be 90
    //gets the sign of the curvature (1 is right, 0 is foward, -1 is left)
    double robotAngle = _source->getAngle();
    int side = getSign(sin(robotAngle) * 
    (lookAheadPoint.position.x - currentPosition.x) - cos(robotAngle) *
    (lookAheadPoint.position.y - currentPosition.y));
    signedCurvature = generateDriveCurve() * side;
    return signedCurvature;
}

void PathFollower::updatePosition() { currentPosition = _source->getPosition(); }

/*
 * Loads path points from a csv file in the format:
 * x position, y position, velocity
 * x position, y position, velocity
 * etc..
 */

std::vector<Point> PathFollower::constructVectorPathCSV(string csvPath) {
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
        point.position.x = pointX;
        point.position.y = pointY;
        point.velocity = velocity;
        xyPath.push_back(point);
        // cout for debugging in the future
        //      std::cout << "x: " << point.x << " | y: " << point.y << " |
        //      velcoity: " << point.velocity << std::endl;
    }
    return xyPath;
}

std::vector<Point> PathFollower::constructVectorPathSeg(Segment *seg, int length) {
    double pointX;
    double pointY;
    double velocity;
    std::vector<Point> xyPath;
    int i = 0;
    for (i = 0; i < length; i++) {
        Segment s = seg[i];

        pointX = s.x;
        pointY = s.y;
        velocity = s.velocity;

        Point point;
        point.position.x = pointX;
        point.position.y = pointY;
        point.velocity = velocity;
        xyPath.push_back(point);
    }
    return xyPath;
}

int PathFollower::getSign(double side){
    int sign;
    if (side > 0) {
        sign = 1;
    }
    else if (side < 0) {
        sign = -1;
    }
    else {
        sign = 0;
    }
    return sign;
}