#include "constants.hpp"
#include "csvcpp.hpp"
#include <tuple>
#include <utility>
#include <vector>

int csvLineCounter = 1; 
bool pointNotFound;

/*  if the distance between the two centres is smaller or equal to the sum of the radii it returns true (they intersect)
    it is squared to avoid using a sqrt
*/
bool circle(double x1, double y1, double x2,  
           double y2, double r1, double r2) { 
    int distSq = (x1 - x2) * (x1 - x2) + 
                 (y1 - y2) * (y1 - y2); 
    int radSumSq = (r1 + r2) * (r1 + r2); 
    if (distSq == radSumSq) 
        return true; 
    else if (distSq > radSumSq) 
        return false; 
    else
        return true; 
} 

int xyPathPointCount = 0;

std::pair<double, double> findLookaheadPoint(double xPos, double yPos, std::vector<std::pair<double, double>> xyPath) {
    std::cout << "checkpoint 1: " << std::endl;
    std::pair<double, double>pathPoints;
    double xPoint, yPoint;
    //keeps track of where our last point was so that we dont have to search the entire vector for the point again 
    bool doTheyIntersect;
    while (pointNotFound){
        //change below
        xPoint = xyPath.at(xyPathPointCount).first;
        yPoint = xyPath.at(xyPathPointCount).second;
        std::cout << "checkpoint 2: " << xPoint << std::endl;
        //if the distance between the two centres of the circles is smaller/equal to the radius, the circles intersect/touch
        doTheyIntersect = circle(xPoint, yPoint, xPos, yPos, pointRadius, lookaheadDistance);
        //check if they intersect, if they do, give that point to the program to follow
        if (doTheyIntersect) {
            pointNotFound = true;
            std::pair <double, double> pathPoints;
            pathPoints.first = xPoint;
            pathPoints.second = yPoint;
            std::cout << "checkpoint 3: " << xPoint << std::endl;
            return pathPoints;
        }
        //not needed, but easier to read: if they dont intersect, the count will increase at it'll analyse the next point
        else {
            xyPathPointCount++;
        }
    }  
}
