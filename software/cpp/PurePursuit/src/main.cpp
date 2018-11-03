#include "csvcpp.hpp"
#include "pointFinder.hpp"
#include <iostream>
#include <utility>

int main()
{
    double xPos = 1.50095;
    double yPos = 1.7231;
    std::pair<double, double>points = findLookaheadPoint(xPos, yPos);
    std::cout << "x: " << points.first << " y: " << points.second << std::endl;
    std::system("PAUSE");
}