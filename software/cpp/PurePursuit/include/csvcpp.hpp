#ifndef _CSV
#define _CSV
#include "csvcpp.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>

// This functions takes a csv file with an x and y header, and puts it all into pairs (doubles) and then into a vector to make it easy to read.
std::vector<std::pair<double, double>> csvXY() {
        std::ifstream data("C:/Users/Tal Donde/Documents/FRC/frc/software/cpp/PurePursuit/test_left.csv");
        std::string line;
        std::vector<std::vector<std::string> > parsedCsv;
        std::vector<std::pair<double, double>>xyPath;
        std::string x, y;
        while(std::getline(data,line)){
                std::stringstream ss(line);
                std::getline(ss, x, ',');
                std::getline(ss, y, ',');
                double pointX = ::atof(x.c_str());
                double pointY = ::atof(y.c_str());
                std::pair<double, double>xyPoints;
                xyPoints.first = pointX;
                xyPoints.second = pointY;
                xyPath.push_back(xyPoints);
                std::system("PAUSE");
        } 
        return xyPath;
}     
#endif