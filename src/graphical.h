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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
#pragma clang diagnostic ignored "-Wreturn-stack-address"

struct Offset {
public:
    double dx;
    double dy;

    static Offset zero() {
        return {0, 0};
    }

    Offset(double dx, double dy) {
        this->dx = dx;
        this->dy = dy;
    }

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

    /// The magnitude of the offset.
    ///
    /// If you need this value to compare it to another [Offset]'s distance,
    /// consider using [distanceSquared] instead, since it is cheaper to compute.
    double distance() const {
        return sqrt(dx * dx + dy * dy);
    }

    double direction() const {
        return atan2(dy, dx);
    }

    Offset operator+(const Offset &other) const {
        return {dx + other.dx, dy + other.dy};
    }

    Offset operator-(const Offset &other) const {
        return {dx - other.dx, dy - other.dy};
    }

    string toJson() const {
        return string()
                .append("\"dx\":")
                .append(to_string(dx))
                .append(",\"dy\":")
                .append(to_string(dy));
    }
};

struct Size {
public:
    double width;
    double height;

    Size(double width, double height) {
        this->width = width;
        this->height = height;
    }

    Size flipped() const {
        return {height, width};
    }

    double direction() const {
        return atan2(height, width);
    }

    double radians() const {
        return flipped().direction();
    }

    double distance() const {
        return direction();
    }

    Offset centerRight(Offset origin) const {
        return {origin.dx + width, origin.dy + height / 2.0};
    }

    /// 半角
    double semiRadians() const {
        return flipped().centerRight(Offset::zero()).direction();
    }

    string toJson() const {
        return string()
                .append("\"width\":")
                .append(to_string(width))
                .append(",\"height\":")
                .append(to_string(height))
                .append(",\"direction\":")
                .append(to_string(direction()))
                .append(",\"radians\":")
                .append(to_string(radians()))
                .append(",\"distance\":")
                .append(to_string(distance()));
    }
};

struct Rect {
public:
    double left;
    double top;
    double right;
    double bottom;

    Rect(double left, double top, double right, double bottom) : left(left), top(top), right(right), bottom(bottom) {}

    static Rect fromCenter(Offset center, double width, double height) {
        return {
                center.dx - width / 2,
                center.dy - height / 2,
                center.dx + width / 2,
                center.dy + height / 2
        };
    }

    static Rect fromCircle(Offset center, double radius) {
        return fromCenter(center, radius * 2, radius * 2);
    }

    string toJson() const {
        return string()
                .append("\"left\":")
                .append(to_string(left))
                .append(",\"top\":")
                .append(to_string(top))
                .append(",\"right\":")
                .append(to_string(right))
                .append(",\"bottom\":")
                .append(to_string(bottom));
    }
};

extern "C" {

const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset);

}

#pragma clang diagnostic pop


#endif //GRAPHICAL_GRAPHICAL_H