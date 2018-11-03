#include "csvcpp.hpp"
#include "pointFinder.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
int main()
{
    double robotX = 1.50095;
    double robotY = 1.7231;
    std::vector<std::pair<double, double>> xyPath;
    xyPath = csvXY();
    std::pair<double, double> point =  findLookaheadPoint(robotX, robotY, xyPath);
    std::cout << "x: " << point.first << " y: " << point.second << std::endl;
    std::system("PAUSE");
}
