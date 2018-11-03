#include "csvcpp.hpp"
#include "pointFinder.hpp"
#include "constants.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
int main()
{
    double robotX = 2.00095;
    double robotY = 2.2231;
    double please;
    please = circle(robotX, robotY, 2.00095, 2.2231, lookaheadDistance, pointRadius);
    std::vector<std::pair<double, double>> xyPath;
    xyPath = csvXY();
    std::pair<double, double> point =  findLookaheadPoint(robotX, robotY, xyPath);
    std::cout << "x:  " << point.first << " y: " << point.second << std::endl;
    std::system("PAUSE");
}
