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

struct Incircle *fromRadians(double radians, double radius) {
    struct Incircle incircle = Incircle::fromRadians(radians, radius);
    return &incircle;
}

struct Incircle *fromSize(double width, double height, double radius, bool avoidOffset) {
    struct Incircle incircle = Incircle::fromSize({width, height}, radius, avoidOffset);
    return &incircle;
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