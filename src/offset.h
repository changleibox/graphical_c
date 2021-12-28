//
// Created by changlei on 2021/12/28.
//

#ifndef GRAPHICAL_OFFSET_H
#define GRAPHICAL_OFFSET_H

#include <cmath>
#include <string>
#include "graphical.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"

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

    Offset operator+(const Offset &other) const {
        return {dx + other.dx, dy + other.dy};
    }

    Offset operator-(const Offset &other) const {
        return {dx - other.dx, dy - other.dy};
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
               dy == rhs.dy &&
               distance == rhs.distance &&
               direction == rhs.direction;
    }

    bool operator!=(const Offset &rhs) const {
        return !(rhs == *this);
    }
};

DART_API struct Offset Offset_init(double dx, double dy);

DART_API struct Offset Offset_fromDirection(double direction, double distance);

#pragma clang diagnostic pop

#endif //GRAPHICAL_OFFSET_H
