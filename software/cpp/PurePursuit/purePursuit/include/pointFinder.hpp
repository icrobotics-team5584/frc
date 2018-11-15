#ifndef _POINTFINDER
#define _POINTFINDER
#include "pointFinder.cpp"
#include <utility>
#include <vector>

bool circle(double, double, double,
            double, double, double);
std::pair<double, double> findLookaheadPoint(double, double, std::vector<std::pair<double, double>>);

#endif