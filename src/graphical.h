//
// Created by changlei on 2021/12/23.
//

#include <string>
#include <cmath>
#include <vector>
#include <sstream>

#ifndef GRAPHICAL_GRAPHICAL_H
#define GRAPHICAL_GRAPHICAL_H

/// 180度对应的弧度
const double r180 = M_PI;

/// 90度对应的弧度
const double r90 = r180 / 2;

/// 90度对应的弧度
const double r270 = r180 * 3 / 2;

/// 360度对应的弧度
const double r360 = r180 * 2;

extern "C" {

struct Offset;

struct Size;

struct Rect;

struct Incircle;

struct Path;

Incircle fromRadians(double radians, double radius);

Incircle fromSize(double width, double height, double radius, bool avoidOffset = false);

const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset);

double pi();

double radians90();

double radians180();

double radians270();

double radians360();

}

#endif //GRAPHICAL_GRAPHICAL_H