#include "purePursuit/include/csvcpp.hpp"
#include "purePursuit/include/pointFinder.hpp"
#include "purePursuit/include/constants.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "purePursuit/include/Point.hpp"
int main_purepursuit()
{
    double robotX = 2;
    double robotY = 2;
    std::vector<Point> xyPath;
    xyPath = csvXY();
    Point point = findVelocityPoint(robotX, robotY, xyPath);
    std::cout << "x:  " << point.x << "| y: " << point.y << "| velocity: " << point.velocity << std::endl;
}
