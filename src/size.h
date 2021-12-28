//
// Created by changlei on 2021/12/28.
//

#ifndef GRAPHICAL_SIZE_H
#define GRAPHICAL_SIZE_H

#include <cmath>
#include <string>
#include <cfloat>
#include "graphical.h"
#include "offset.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "ArgumentSelectionDefects"

struct Size {
public:
    const double width;
    const double height;

    Size(double width, double height) : width(width), height(height) {}

    static Size copy(Size source) {
        return {source.width, source.height};
    }

    static Size square(double dimension) {
        return {dimension, dimension};
    }

    static Size fromWidth(double width) {
        return {width, DBL_MAX};
    }

    static Size fromHeight(double height) {
        return {DBL_MAX, height};
    }

    static Size fromRadius(double radius) {
        return {radius * 2, radius * 2};
    }

    double aspectRatio() const {
        if (height != 0.0) {
            return width / height;
        }
        if (width > 0.0) {
            return DBL_MAX;
        }
        if (width < 0.0) {
            return -DBL_MAX;
        }
        return 0.0;
    }

    const double direction{atan2(height, width)};

    const double radians{atan2(width, height)};

    const double distance{direction};

    /// 半角
    const double semiRadians{atan2(height, width / 2)};

    /// The lesser of the magnitudes of the [width] and the [height].
    double shortestSide{min(abs(width), abs(height))};

    /// The greater of the magnitudes of the [width] and the [height].
    double longestSide{max(abs(width), abs(height))};

    // Convenience methods that do the equivalent of calling the similarly named
    // methods on a Rect constructed from the given origin and this size.

    /// The offset to the intersection of the top and left edges of the rectangle
    /// described by the given [Offset] (which is interpreted as the top-left corner)
    /// and this [Size].
    ///
    /// See also [Rect.topLeft].
    Offset topLeft(Offset origin) const { // NOLINT(readability-convert-member-functions-to-static)
        return origin;
    }

    /// The offset to the center of the top edge of the rectangle described by the
    /// given offset (which is interpreted as the top-left corner) and this size.
    ///
    /// See also [Rect.topCenter].
    Offset topCenter(Offset origin) const {
        return {origin.dx + width / 2.0, origin.dy};
    }

    /// The offset to the intersection of the top and right edges of the rectangle
    /// described by the given offset (which is interpreted as the top-left corner)
    /// and this size.
    ///
    /// See also [Rect.topRight].
    Offset topRight(Offset origin) const {
        return {origin.dx + width, origin.dy};
    }

    /// The offset to the center of the left edge of the rectangle described by the
    /// given offset (which is interpreted as the top-left corner) and this size.
    ///
    /// See also [Rect.centerLeft].
    Offset centerLeft(Offset origin) const {
        return {origin.dx, origin.dy + height / 2.0};
    }

    /// The offset to the point halfway between the left and right and the top and
    /// bottom edges of the rectangle described by the given offset (which is
    /// interpreted as the top-left corner) and this size.
    ///
    /// See also [Rect.center].
    Offset center(Offset origin) const {
        return {origin.dx + width / 2.0, origin.dy + height / 2.0};
    }

    /// The offset to the center of the right edge of the rectangle described by the
    /// given offset (which is interpreted as the top-left corner) and this size.
    ///
    /// See also [Rect.centerLeft].
    Offset centerRight(Offset origin) const {
        return {origin.dx + width, origin.dy + height / 2.0};
    }

    /// The offset to the intersection of the bottom and left edges of the
    /// rectangle described by the given offset (which is interpreted as the
    /// top-left corner) and this size.
    ///
    /// See also [Rect.bottomLeft].
    Offset bottomLeft(Offset origin) const {
        return {origin.dx, origin.dy + height};
    }

    /// The offset to the center of the bottom edge of the rectangle described by
    /// the given offset (which is interpreted as the top-left corner) and this
    /// size.
    ///
    /// See also [Rect.bottomLeft].
    Offset bottomCenter(Offset origin) const {
        return {origin.dx + width / 2.0, origin.dy + height};
    }

    /// The offset to the intersection of the bottom and right edges of the
    /// rectangle described by the given offset (which is interpreted as the
    /// top-left corner) and this size.
    ///
    /// See also [Rect.bottomRight].
    Offset bottomRight(Offset origin) const {
        return {origin.dx + width, origin.dy + height};
    }

    /// Whether the point specified by the given offset (which is assumed to be
    /// relative to the top left of the size) lies between the left and right and
    /// the top and bottom edges of a rectangle of this size.
    ///
    /// Rectangles include their top and left edges but exclude their bottom and
    /// right edges.
    bool contains(Offset offset) const {
        return offset.dx >= 0.0 && offset.dx < width && offset.dy >= 0.0 && offset.dy < height;
    }

    /// A [Size] with the [width] and [height] swapped.
    Size flipped() const {
        return {height, width};
    }

    string toJson() const {
        return string()
                .append("{")
                .append("\"width\":")
                .append(to_string(width))
                .append(",\"height\":")
                .append(to_string(height))
                .append(",\"direction\":")
                .append(to_string(direction))
                .append(",\"radians\":")
                .append(to_string(radians))
                .append(",\"distance\":")
                .append(to_string(distance))
                .append("}");
    }

    bool operator==(const Size &rhs) const {
        return width == rhs.width &&
               height == rhs.height &&
               direction == rhs.direction &&
               radians == rhs.radians &&
               distance == rhs.distance &&
               semiRadians == rhs.semiRadians;
    }

    bool operator!=(const Size &rhs) const {
        return !(rhs == *this);
    }
};

DART_API struct Size Size_init(double width, double height);

DART_API struct Size Size_copy(Size source);

DART_API struct Size Size_square(double dimension);

DART_API struct Size Size_fromWidth(double width);

DART_API struct Size Size_fromHeight(double height);

DART_API struct Size Size_fromRadius(double radius);

#pragma clang diagnostic pop

#endif //GRAPHICAL_SIZE_H
