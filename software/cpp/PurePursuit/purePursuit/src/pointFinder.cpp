#include "constants.hpp"
#include "csvcpp.hpp"
#include <tuple>
#include <utility>
#include <vector>
#include <typeinfo>
#include <cmath>


/*  if the distance between the two centres is smaller or equal to the sum of the radii it returns true (they intersect)
    it is squared to avoid using a sqrt (because who likes those amiright)
*/
bool circle(double x1, double y1, double x2,  
           double y2, double r1, double r2) { 
    double distSq = (x2-x1) * (x2 - x1) + 
                 (y2 - y1) * (y2 - y1); 
    double radSumSq = (r1 + r2) * (r1 + r2); 
    //if they distance is greater than the sum of the two triangles, they are not touching
    if (distSq > radSumSq) 
        return false;
    //this checks whether it circle is inside the other
    else if (distSq < std::abs(r1-r2)) 
        return false;
    //check whether they are the same circle (will not happen in our current situation, since the radiuses are different, but just in case)
    else if ((distSq == 0) && (r1 = r2))
        return false;
    else if (distSq < radSumSq)
        return true;
    else
        return false;
} 
//starts at -1 so that when the while loop is played it goes to 0
int xyPathPointCount = -1;
bool pointNotFound = false;

std::pair<double, double> findLookaheadPoint(double xPos, double yPos, std::vector<std::pair<double, double>> xyPath) {
    std::pair<double, double>pathPoints;
    double xPoint, yPoint;
    //keeps track of where our last point was so that we dont have to search the entire vector for the point again 
    bool doTheyIntersect = false;
    //check if they intersect, if they do, give that point to the program to follow
    while (!doTheyIntersect){
        xyPathPointCount++;
        xPoint = xyPath.at(xyPathPointCount).first;
        yPoint = xyPath.at(xyPathPointCount).second;
        //if the distance between the two centres of the circles is smaller/equal to the radius, the circles intersect/touch
        doTheyIntersect = circle(xPoint, yPoint, xPos, yPos, pointRadius, lookaheadDistance);
        //std::cout << "x: " << xPoint << " y: " << yPoint <<" intecept?" << doTheyIntersect << std::endl;
        }
    pathPoints.first = xPoint;
    pathPoints.second = yPoint;
    return pathPoints;
    }  
