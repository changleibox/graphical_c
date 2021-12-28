//
// Created by changlei on 2021/12/23.
//


#include <string>
#include <cmath>
#include <vector>
#include <sstream>

#define DART_API extern "C" __attribute__((visibility("default"))) __attribute__((used))

#ifndef GRAPHICAL_GRAPHICAL_H
#define GRAPHICAL_GRAPHICAL_H

#pragma pack(1)

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

/// 180度对应的弧度
const double r180 = M_PI;

/// 90度对应的弧度
const double r90 = r180 / 2;

/// 90度对应的弧度
const double r270 = r180 * 3 / 2;

/// 360度对应的弧度
const double r360 = r180 * 2;

DART_API struct Path Graphical_cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset);

DART_API double Graphical_pi();

DART_API double Graphical_radians90();

DART_API double Graphical_radians180();

DART_API double Graphical_radians270();

DART_API double Graphical_radians360();

#pragma clang diagnostic pop

#pragma pack()

#endif //GRAPHICAL_GRAPHICAL_H