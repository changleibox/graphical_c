//
// Created by changlei on 2021/12/28.
//

#pragma once

#ifndef GRAPHICAL_OFFSET_H
#define GRAPHICAL_OFFSET_H


#include <cmath>
#include <string>
#include <cfloat>
#include <ostream>
#include "graphical.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Offset {
public:
    const double dx;
    const double dy;

    Offset(double dx, double dy) : dx(dx), dy(dy) {}

    /// The magnitude of the offset.
    ///
    /// If you need this value to compare it to another [Offset]'s distance,
    /// consider using [distanceSquared] instead, since it is cheaper to compute.
    const double distance{sqrt(dx * dx + dy * dy)};

    const double distanceSquared{pow(dx, 2) + pow(dy, 2)};

    const double direction{atan2(dy, dx)};

    /// 绕X轴旋转
    Offset rotationX(double radians) const {
        return {dx, dy * cos(radians)};
    }

    /// 绕Y轴旋转
    Offset rotationY(double radians) const {
        return {dx * cos(radians), dy};
    }

    /// 绕Z轴旋转
    Offset rotationZ(double radians) const {
        double newCos = cos(radians);
        double newSin = sin(radians);
        return {dx * newCos - dy * newSin, dy * newCos + dx * newSin};
    }

    Offset operator-() const {
        return {-dx, -dy};
    }

    Offset operator+(const Offset &other) const {
        return {dx + other.dx, dy + other.dy};
    }

    Offset operator-(const Offset &other) const {
        return {dx - other.dx, dy - other.dy};
    }

    Offset operator*(double operand) const {
        return {dx * operand, dy * operand};
    }

    Offset operator/(double operand) const {
        return {dx / operand, dy / operand};
    }

    bool isInfinite() const {
        return dx >= DBL_MAX || dy >= DBL_MAX;
    }

    bool isFinite() const {
        return !isinf(dx) && !isinf(dy);
    }

    bool operator<(const Offset &other) const {
        return dx < other.dx && dy < other.dy;
    }

    bool operator<=(const Offset &other) const {
        return dx <= other.dx && dy <= other.dy;
    }

    bool operator>(const Offset &other) const {
        return dx > other.dx && dy > other.dy;
    }

    bool operator>=(const Offset &other) const {
        return dx >= other.dx && dy >= other.dy;
    }

    string toJson() const {
        return string()
                .append("{")
                .append("\"dx\":")
                .append(to_string(dx))
                .append(",\"dy\":")
                .append(to_string(dy))
                .append("}");
    }

    bool operator==(const Offset &rhs) const {
        return dx == rhs.dx &&
               dy == rhs.dy;
    }

    bool operator!=(const Offset &rhs) const {
        return !(rhs == *this);
    }

    friend ostream &operator<<(ostream &os, const Offset &offset) {
        os << "dx: " << offset.dx << " dy: " << offset.dy;
        return os;
    }
};

DART_API struct Offset Offset_init(double dx, double dy);

DART_API struct Offset Offset_fromDirection(double direction, double distance);

DART_API struct Offset Offset_rotationX(Offset offset, double radians);

DART_API struct Offset Offset_rotationY(Offset offset, double radians);

DART_API struct Offset Offset_rotationZ(Offset offset, double radians);

#pragma clang diagnostic pop


#endif //GRAPHICAL_OFFSET_H
