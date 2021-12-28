//
// Created by changlei on 2021/12/28.
//

#include "size.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Size Size_init(double width, double height) {
    return {width, height};
}

struct Size Size_copy(Size source) {
    return Size::copy(source);
}

struct Size Size_square(double dimension) {
    return Size::square(dimension);
}

struct Size Size_fromWidth(double width) {
    return Size::fromWidth(width);
}

struct Size Size_fromHeight(double height) {
    return Size::fromHeight(height);
}

struct Size Size_fromRadius(double radius) {
    return Size::fromRadius(radius);
}

double Size_aspectRatio(Size size) {
    return size.aspectRatio();
}

struct Offset Size_topLeft(Size size, Offset origin) {
    return size.topLeft(origin);
}

struct Offset Size_topCenter(Size size, Offset origin) {
    return size.topCenter(origin);
}

struct Offset Size_topRight(Size size, Offset origin) {
    return size.topRight(origin);
}

struct Offset Size_centerLeft(Size size, Offset origin) {
    return size.centerLeft(origin);
}

struct Offset Size_center(Size size, Offset origin) {
    return size.center(origin);
}

struct Offset Size_centerRight(Size size, Offset origin) {
    return size.centerRight(origin);
}

struct Offset Size_bottomLeft(Size size, Offset origin) {
    return size.bottomLeft(origin);
}

struct Offset Size_bottomCenter(Size size, Offset origin) {
    return size.bottomCenter(origin);
}

struct Offset Size_bottomRight(Size size, Offset origin) {
    return size.bottomRight(origin);
}

bool Size_contains(Size size, Offset offset) {
    return size.contains(offset);
}

struct Size Size_flipped(Size size) {
    return size.flipped();
}

#pragma clang diagnostic pop
