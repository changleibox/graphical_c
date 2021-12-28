//
// Created by changlei on 2021/12/28.
//

#include "rect.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Rect Rect_init(double left, double top, double right, double bottom) {
    return {left, top, right, bottom};
}

struct Rect Rect_fromLTWH(double left, double top, double width, double height) {
    return Rect::fromLTWH(left, top, width, height);
}

struct Rect Rect_fromCircle(Offset center, double radius) {
    return Rect::fromCircle(center, radius);
}

struct Rect Rect_formCenter(Offset center, double width, double height) {
    return Rect::fromCenter(center, width, height);
}

struct Rect Rect_fromPoints(Offset a, Offset b) {
    return Rect::fromPoints(a, b);
}

struct Rect shift(Rect rect, Offset offset) {
    return rect.shift(offset);
}

struct Rect translate(Rect rect, double translateX, double translateY) {
    return rect.translate(translateX, translateY);
}

struct Rect inflate(Rect rect, double delta) {
    return rect.inflate(delta);
}

struct Rect deflate(Rect rect, double delta) {
    return rect.deflate(delta);
}

struct Rect intersect(Rect rect, Rect other) {
    return rect.intersect(other);
}

struct Rect expandToInclude(Rect rect, Rect other) {
    return rect.expandToInclude(other);
}

bool overlaps(Rect rect, Rect other) {
    return rect.overlaps(other);
}

bool contains(Rect rect, Offset offset) {
    return rect.contains(offset);
}

#pragma clang diagnostic pop
