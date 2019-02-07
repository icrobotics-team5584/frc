# 5584's Pure Pursuit Controller

Files:

* csvcpp.hpp
* pointFinder.cpp
* constants.hpp
* pointFinder.hpp

## What do they do?

* csvcpp.hpp

This reads a csv file and parses it into a vector of pairs. It is designed to only take csv files with x and y co ords, and no header. 

* pointFinder.cpp

This has two functions in it. One is circle() and the other findLookaheadPoint(). What it does is look at the vector that we made before
and compares it with the current robot location. Using the constants in constants.hpp as a radius, it finds whether the two circles
intersect. If they do, then it returns that point for the robot to then pursue. 

If you want to run and try out this code, you can use the following int main() function:

```cpp
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
    std::vector<std::pair<double, double>> xyPath;
    xyPath = csvXY();
    std::pair<double, double> point = findLookaheadPoint(robotX, robotY, xyPath);
    std::cout << "x:  " << point.first << " y: " << point.second<< std::endl;
    std::system("PAUSE");
}
```
