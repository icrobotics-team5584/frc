#include "csvcpp.hpp"
#include "pointFinder.hpp"
#include "constants.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <Point.hpp>
int main()
{
    double robotX = 2.00095;
    double robotY = 2.2231;
    std::vector<Point> xyPath;
    xyPath = csvXY();
    Point point = findLookaheadPoint(robotX, robotY, xyPath);
    std::cout << "x:  " << point.x << "| y: " << point.y << std::endl;
}
