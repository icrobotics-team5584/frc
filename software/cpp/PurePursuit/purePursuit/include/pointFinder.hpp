#ifndef _POINTFINDER
#define _POINTFINDER
#include <utility>
#include <vector>
#include "Point.hpp"

bool circle(double, double, double,
            double, double, double);
Point findLookaheadPoint(double, double, std::vector<Point>);

#endif