#include "constants.hpp"
#include "csvcpp.hpp"
#include <tuple>
#include <utility>

int csvLineCounter = 1; 
bool pointNotFound;

/*  if the distance between the two centres is smaller or equal to the sum of the radii it returns true (they intersect)
    it is squared to avoid using a sqrt
*/
bool circle(double x1, double y1, double x2,  
           double y2, double r1, double r2) 
{ 
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

//
std::pair<double, double> findLookaheadPoint(double xPos, double yPos) {
    std::pair<double, double>pathPoints;
    double xPoint, yPoint;
    bool doTheyIntersect;
    while (pointNotFound){
        //get the x and y co ords for the point on the path.
        pathPoints = csvXY(csvLineCounter);
        xPoint = pathPoints.first;
        yPoint = pathPoints.second;
        //tells the program what point we are at on the csv file (so we don't search the entire thing every time)
        ++csvLineCounter;
        //if the distance between the two centres of the circles is smaller/equal to the radius, the circles intersect/touch
        doTheyIntersect = circle(xPoint, yPoint, xPos, yPos, pointRadius, lookaheadDistance);
        //check if they intersect, if they do, give that point to the program to follow
        if (doTheyIntersect) {
            pointNotFound = true;
            std::pair <double, double> pathPoints;
            pathPoints.first = xPoint;
            pathPoints.second = yPoint;
            return pathPoints;
        }
    }  
}
