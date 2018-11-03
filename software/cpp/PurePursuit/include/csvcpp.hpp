#ifndef _CSV
#define _CSV
#include "csvcpp.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>

//function that takes in a linenumber and returns the x,y values of that line respectively. Takes this data from the csv file in the first line
//of the function
std::pair<double, double> csvXY(int lineNumber) {
    std::ifstream data("C:/Users/Tal Donde/Documents/FRC/frc/software/cpp/PurePursuit/test_left.csv");
    std::string line;
    std::vector<std::vector<std::string> > parsedCsv;
    std::string x, y;
    data.ignore(lineNumber, '\n');
    std::getline(data,line);
    std::stringstream ss(line);
    std::getline(ss, x, ',');
    std::getline(ss, y, ',');
    double pointX = ::atof(x.c_str());
    double pointY = ::atof(y.c_str());
    std::pair<double, double>xyPoints;
    xyPoints.first = pointX;
    xyPoints.second = pointY;
    std::cout << "checkpoint 1: " << pointX << std::endl;
    std::system("PAUSE");
    //this program usually loops till the csv file ends, but that broken by the return (intentional)
    return xyPoints;
    
}
#endif