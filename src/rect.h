//
// Created by changlei on 2021/12/28.
//

#pragma once

#ifndef GRAPHICAL_RECT_H
#define GRAPHICAL_RECT_H


#include "size.h"
#include "offset.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Rect {
public:
    const double left;
    const double top;
    const double right;
    const double bottom;

    Rect(double left, double top, double right, double bottom) : left(left), top(top), right(right), bottom(bottom) {}

    double width{right - left};

    double height{bottom - top};

    Size size{Size(right - left, bottom - top)};

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

    static Rect fromLTWH(double left, double top, double width, double height) {
        return {left, top, left + width, top + height};
    }

    static Rect fromPoints(Offset a, Offset b) {
        return {min(a.dx, b.dx), min(a.dy, b.dy), max(a.dx, b.dx), max(a.dy, b.dy)};
    }

    Rect shift(Offset offset) const {
        return {left + offset.dx, top + offset.dy, right + offset.dx, bottom + offset.dy};
    }

    Rect translate(double translateX, double translateY) const {
        return {left + translateX, top + translateY, right + translateX, bottom + translateY};
    }

    Rect inflate(double delta) const {
        return {left - delta, top - delta, right + delta, bottom + delta};
    }

    Rect deflate(double delta) const {
        return inflate(-delta);
    }

    Rect intersect(Rect other) const {
        return {
                max(left, other.left),
                max(top, other.top),
                min(right, other.right),
                min(bottom, other.bottom)
        };
    }

    Rect expandToInclude(Rect other) const {
        return {
                min(left, other.left),
                min(top, other.top),
                max(right, other.right),
                max(bottom, other.bottom)
        };
    }

    bool overlaps(Rect other) const {
        if (right <= other.left || other.right <= left) {
            return false;
        }
        if (bottom <= other.top || other.bottom <= top) {
            return false;
        }
        return true;
    }

    /// The lesser of the magnitudes of the [width] and the [height] of this
    /// rectangle.
    double shortestSide{min(abs(width), abs(height))};

    /// The greater of the magnitudes of the [width] and the [height] of this
    /// rectangle.
    double longestSide{max(abs(width), abs(height))};

    /// The offset to the intersection of the top and left edges of this rectangle.
    ///
    /// See also [Size.topLeft].
    Offset topLeft{Offset(left, top)};

    /// The offset to the center of the top edge of this rectangle.
    ///
    /// See also [Size.topCenter].
    Offset topCenter{Offset(left + width / 2.0, top)};

    /// The offset to the intersection of the top and right edges of this rectangle.
    ///
    /// See also [Size.topRight].
    Offset topRight{Offset(right, top)};

    /// The offset to the center of the left edge of this rectangle.
    ///
    /// See also [Size.centerLeft].
    Offset centerLeft{Offset(left, top + height / 2.0)};

    /// The offset to the point halfway between the left and right and the top and
    /// bottom edges of this rectangle.
    ///
    /// See also [Size.center].
    Offset center{Offset(left + width / 2.0, top + height / 2.0)};

    /// The offset to the center of the right edge of this rectangle.
    ///
    /// See also [Size.centerLeft].
    Offset centerRight{Offset(right, top + height / 2.0)};

    /// The offset to the intersection of the bottom and left edges of this rectangle.
    ///
    /// See also [Size.bottomLeft].
    Offset bottomLeft{Offset(left, bottom)};

    /// The offset to the center of the bottom edge of this rectangle.
    ///
    /// See also [Size.bottomLeft].
    Offset bottomCenter{Offset(left + width / 2.0, bottom)};

    /// The offset to the intersection of the bottom and right edges of this rectangle.
    ///
    /// See also [Size.bottomRight].
    Offset bottomRight{Offset(right, bottom)};

    /// Whether the point specified by the given offset (which is assumed to be
    /// relative to the origin) lies between the left and right and the top and
    /// bottom edges of this rectangle.
    ///
    /// Rectangles include their top and left edges but exclude their bottom and
    /// right edges.
    bool contains(Offset offset) const {
        return offset.dx >= left && offset.dx < right && offset.dy >= top && offset.dy < bottom;
    }

    bool isInfinite() const {
        return left >= DBL_MAX || top >= DBL_MAX || right >= DBL_MAX || bottom >= DBL_MAX;
    }

    bool isFinite() const {
        return !isinf(left) && !isinf(top) && !isinf(right) && !isinf(bottom);
    }

    bool isEmpty() const {
        return left >= right || top >= bottom;
    }

    string toJson() const {
        return string()
                .append("{")
                .append("\"left\":")
                .append(to_string(left))
                .append(",\"top\":")
                .append(to_string(top))
                .append(",\"right\":")
                .append(to_string(right))
                .append(",\"bottom\":")
                .append(to_string(bottom))
                .append(",\"size\":")
                .append(size.toJson())
                .append("}");
    }

    bool operator==(const Rect &rhs) const {
        return left == rhs.left &&
               top == rhs.top &&
               right == rhs.right &&
               bottom == rhs.bottom;
    }

    bool operator!=(const Rect &rhs) const {
        return !(rhs == *this);
    }
};

DART_API struct Rect Rect_init(double left, double top, double right, double bottom);

DART_API struct Rect Rect_fromLTWH(double left, double top, double width, double height);

DART_API struct Rect Rect_fromCircle(Offset center, double radius);

DART_API struct Rect Rect_formCenter(Offset center, double width, double height);

DART_API struct Rect Rect_fromPoints(Offset a, Offset b);

DART_API struct Rect shift(Rect rect, Offset offset);

DART_API struct Rect translate(Rect rect, double translateX, double translateY);

DART_API struct Rect inflate(Rect rect, double delta);

DART_API struct Rect deflate(Rect rect, double delta);

DART_API struct Rect intersect(Rect rect, Rect other);

DART_API struct Rect expandToInclude(Rect rect, Rect other);

DART_API bool overlaps(Rect rect, Rect other);

DART_API bool contains(Rect rect, Offset offset);

#pragma clang diagnostic pop


#endif //GRAPHICAL_RECT_H