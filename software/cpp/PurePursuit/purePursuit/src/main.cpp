#include "csvcpp.hpp"
#include "pointFinder.hpp"
#include "constants.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <Point.hpp>
int main()
{
    double robotX = 2;
    double robotY = 2;
    std::vector<Point> xyPath;
    xyPath = csvXY();
    Point point = findVelocityPoint(robotX, robotY, xyPath);
    std::cout << "x:  " << point.x << "| y: " << point.y << "| velocity: " << point.velocity << std::endl;
}
