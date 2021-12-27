//
// Created by changlei on 2021/12/23.
//

#include <string>
#include <cmath>
#include <vector>
#include <sstream>

using namespace std;

/// 180度对应的弧度
const double radians180 = M_PI;

/// 90度对应的弧度
const double radians90 = radians180 / 2;

/// 90度对应的弧度
const double radians270 = radians180 * 3 / 2;

/// 360度对应的弧度
const double radians360 = radians180 * 2;

#ifndef GRAPHICAL_GRAPHICAL_H
#define GRAPHICAL_GRAPHICAL_H

extern "C" {

const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset);

}

#endif //GRAPHICAL_GRAPHICAL_H