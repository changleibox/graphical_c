//
// Created by changlei on 2021/12/28.
//

#include "incircle.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Incircle Incircle_init(Offset begin, Offset middle, Offset end) {
    return {begin, middle, end};
}

struct Incircle Incircle_fromRadians(double radians, double radius) {
    return Incircle::fromRadians(radians, radius);
}

struct Incircle Incircle_fromSize(Size size, double radius, bool avoidOffset) {
    return Incircle::fromSize(size, radius, avoidOffset);
}

struct Incircle Incircle_shift(Incircle incircle, Offset offset) {
    return incircle.shift(offset);
}

struct Incircle Incircle_rotationX(Incircle incircle, double newRadians) {
    return incircle.rotationX(newRadians);
}

struct Incircle Incircle_rotationY(Incircle incircle, double newRadians) {
    return incircle.rotationY(newRadians);
}

struct Incircle Incircle_rotationZ(Incircle incircle, double newRadians) {
    return incircle.rotationZ(newRadians);
}

struct Incircle Incircle_flipped(Incircle incircle) {
    return incircle.flipped();
}

double Incircle_correctRadians(double radians) {
    return Incircle::correctRadians(radians);
}

double Incircle_offsetOf(Size size, double radius) {
    return Incircle::offsetOf(size, radius);
}

struct Offset Incircle_centerOf(Offset point1, Offset point2, Offset point3) {
    return Incircle::centerOf(point1, point2, point3);
}

#pragma clang diagnostic pop