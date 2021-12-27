//
// Created by changlei on 2021/12/23.
//

#include "graphical.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"

struct Path {
public:
    const struct Incircle top;
    const struct Incircle left;
    const struct Incircle right;

    Path(Incircle top, Incircle left, Incircle right) : top(std::move(top)), left(std::move(left)), right(std::move(right)) {}

    string toJson() const {
        return string()
                .append("{")
                .append("\"top\":")
                .append(top.toJson())
                .append(",\"left\":")
                .append(left.toJson())
                .append(",\"right\":")
                .append(right.toJson())
                .append("}");
    }

    bool operator==(const Path &rhs) const {
        return top == rhs.top &&
               left == rhs.left &&
               right == rhs.right;
    }

    bool operator!=(const Path &rhs) const {
        return !(rhs == *this);
    }
};

struct Incircle *Incircle_fromRadians(double radians, double radius) {
    struct Incircle incircle = Incircle::fromRadians(radians, radius);
    return &incircle;
}

struct Incircle *Incircle_fromSize(double width, double height, double radius, bool avoidOffset) {
    struct Incircle incircle = Incircle::fromSize({width, height}, radius, avoidOffset);
    return &incircle;
}

struct Incircle *Incircle_shift(Incircle *incircle, double dx, double dy) {
    struct Incircle newIncircle = incircle->shift({dx, dy});
    return &newIncircle;
}

struct Incircle *Incircle_rotationX(Incircle *incircle, double newRadians) {
    struct Incircle newIncircle = incircle->rotationX(newRadians);
    return &newIncircle;
}

struct Incircle *Incircle_rotationY(Incircle *incircle, double newRadians) {
    struct Incircle newIncircle = incircle->rotationY(newRadians);
    return &newIncircle;
}

struct Incircle *Incircle_rotationZ(Incircle *incircle, double newRadians) {
    struct Incircle newIncircle = incircle->rotationZ(newRadians);
    return &newIncircle;
}

struct Incircle *Incircle_flipped(Incircle *incircle) {
    struct Incircle newIncircle = incircle->flipped();
    return &newIncircle;
}

const char *Incircle_toJson(Incircle *incircle) {
    const string &json = incircle->toJson();
    char *str = new char[strlen(json.c_str()) + 1];
    return strcpy(str, json.c_str());
}

double Incircle_correctRadians(double radians) {
    return Incircle::correctRadians(radians);
}

double Incircle_offsetOf(Size size, double radius) {
    return Incircle::offsetOf(size, radius);
}

Offset Incircle_centerOf(Offset point1, Offset point2, Offset point3) {
    return Incircle::centerOf(point1, point2, point3);
}

/// 创建各个角
const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset) {
    const Size size = Size(width, height);
    const double topRadius = radius;
    const double leftRadius = blRadius;
    const double rightRadius = brRadius;

    const double topRadians = size.semiRadians;
    const Offset topOffset = Offset(width / 2, 0);
    const Incircle top = Incircle::fromSize(size, topRadius, avoidOffset).shift(topOffset);

    const double leftRadians = (r90 + topRadians) / 2;
    const double leftRotation = r90 + leftRadians;
    const Offset leftOffset = Offset(0, height);
    const Incircle left = Incircle::fromRadians(leftRadians, leftRadius).rotationZ(leftRotation).shift(leftOffset);

    const double rightRadians = (r90 + topRadians) / 2;
    const double rightRotation = r270 - leftRadians;
    const Offset rightOffset = Offset(width, height);
    const Incircle right = Incircle::fromRadians(rightRadians, rightRadius).rotationZ(rightRotation).shift(rightOffset);
    const Path path = {top, left, right};
    const string &json = path.toJson();
    char *str = new char[strlen(json.c_str()) + 1];
    return strcpy(str, json.c_str());
}

double pi() {
    return M_PI;
}

double radians90() {
    return r90;
}

double radians180() {
    return r180;
}

double radians270() {
    return r270;
}

double radians360() {
    return r360;
}

#pragma clang diagnostic pop