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

#pragma clang diagnostic pop
