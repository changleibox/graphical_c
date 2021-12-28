//
// Created by changlei on 2021/12/28.
//

#include "incircle.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct incircle Incircle_fromRadians(double radians, double radius) {
    struct incircle incircle = incircle::fromRadians(radians, radius);
    return incircle;
}

struct incircle Incircle_fromSize(Size size, double radius, bool avoidOffset) {
    struct incircle incircle = incircle::fromSize(size, radius, avoidOffset);
    return incircle;
}

struct incircle Incircle_shift(incircle incircle, Offset offset) {
    struct incircle newIncircle = incircle.shift(offset);
    return newIncircle;
}

struct incircle Incircle_rotationX(incircle incircle, double newRadians) {
    struct incircle newIncircle = incircle.rotationX(newRadians);
    return newIncircle;
}

struct incircle Incircle_rotationY(incircle incircle, double newRadians) {
    struct incircle newIncircle = incircle.rotationY(newRadians);
    return newIncircle;
}

struct incircle Incircle_rotationZ(incircle incircle, double newRadians) {
    struct incircle newIncircle = incircle.rotationZ(newRadians);
    return newIncircle;
}

struct incircle Incircle_flipped(incircle incircle) {
    struct incircle newIncircle = incircle.flipped();
    return newIncircle;
}

double Incircle_correctRadians(double radians) {
    return incircle::correctRadians(radians);
}

double Incircle_offsetOf(Size size, double radius) {
    return incircle::offsetOf(size, radius);
}

struct Offset Incircle_centerOf(Offset point1, Offset point2, Offset point3) {
    return incircle::centerOf(point1, point2, point3);
}

#pragma clang diagnostic pop