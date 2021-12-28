//
// Created by changlei on 2021/12/28.
//

#include "incircle.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Incircle Incircle_fromRadians(double radians, double radius) {
    struct Incircle incircle = Incircle::fromRadians(radians, radius);
    return incircle;
}

struct Incircle Incircle_fromSize(Size size, double radius, bool avoidOffset) {
    struct Incircle incircle = Incircle::fromSize(size, radius, avoidOffset);
    return incircle;
}

struct Incircle Incircle_shift(Incircle incircle, Offset offset) {
    struct Incircle newIncircle = incircle.shift(offset);
    return newIncircle;
}

struct Incircle Incircle_rotationX(Incircle incircle, double newRadians) {
    struct Incircle newIncircle = incircle.rotationX(newRadians);
    return newIncircle;
}

struct Incircle Incircle_rotationY(Incircle incircle, double newRadians) {
    struct Incircle newIncircle = incircle.rotationY(newRadians);
    return newIncircle;
}

struct Incircle Incircle_rotationZ(Incircle incircle, double newRadians) {
    struct Incircle newIncircle = incircle.rotationZ(newRadians);
    return newIncircle;
}

struct Incircle Incircle_flipped(Incircle incircle) {
    struct Incircle newIncircle = incircle.flipped();
    return newIncircle;
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