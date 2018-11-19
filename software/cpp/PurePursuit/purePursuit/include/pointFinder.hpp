#ifndef _POINTFINDER
#define _POINTFINDER
#include "Point.hpp"
#include <utility>
#include <vector>

bool circle(double, double, double,
            double, double, double);
Point findLookaheadPoint(double, double, std::vector<Point>);

Point findVelocityPoint(double, double, std::vector<Point>);

#endif