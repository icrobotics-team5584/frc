#ifndef _POINTFINDER
#define _POINTFINDER
#include "pointFinder.cpp"
#include <utility>

bool circle(double, double, double,
            double, double, double);
std::pair<double, double> findLookaheadPoint(double, double);

#endif