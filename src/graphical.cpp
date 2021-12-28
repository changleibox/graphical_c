//
// Created by changlei on 2021/12/23.
//

#include "graphical.h"
#include "size.h"
#include "offset.h"
#include "incircle.h"
#include "path.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"

struct Path Graphical_cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset) {
    const Size size = Size(width, height);
    const double topRadius = radius;
    const double leftRadius = blRadius;
    const double rightRadius = brRadius;

    const double topRadians = size.semiRadians;
    const Offset topOffset = Offset(width / 2, 0);
    const incircle top = incircle::fromSize(size, topRadius, avoidOffset).shift(topOffset);

    const double leftRadians = (r90 + topRadians) / 2;
    const double leftRotation = r90 + leftRadians;
    const Offset leftOffset = Offset(0, height);
    const incircle left = incircle::fromRadians(leftRadians, leftRadius).rotationZ(leftRotation).shift(leftOffset);

    const double rightRadians = (r90 + topRadians) / 2;
    const double rightRotation = r270 - leftRadians;
    const Offset rightOffset = Offset(width, height);
    const incircle right = incircle::fromRadians(rightRadians, rightRadius).rotationZ(rightRotation).shift(rightOffset);
    return {top, left, right};
}

double Graphical_pi() {
    return M_PI;
}

double Graphical_radians90() {
    return r90;
}

double Graphical_radians180() {
    return r180;
}

double Graphical_radians270() {
    return r270;
}

double Graphical_radians360() {
    return r360;
}

#pragma clang diagnostic pop