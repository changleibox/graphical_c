//
// Created by changlei on 2021/12/28.
//

#include "offset.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Offset Offset_init(double dx, double dy) {
    return {dx, dy};
}

struct Offset Offset_fromDirection(double direction, double distance) {
    return {distance * cos(direction), distance * sin(direction)};
}

struct Offset Offset_rotationX(Offset offset, double radians) {
    return offset.rotationX(radians);
}

struct Offset Offset_rotationY(Offset offset, double radians) {
    return offset.rotationY(radians);
}

struct Offset Offset_rotationZ(Offset offset, double radians) {
    return offset.rotationZ(radians);
}

#pragma clang diagnostic pop