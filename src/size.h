//
// Created by changlei on 2021/12/28.
//

#ifndef GRAPHICAL_SIZE_H
#define GRAPHICAL_SIZE_H

#include <cmath>
#include <string>
#include "graphical.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"

struct Size {
public:
    const double width;
    const double height;

    Size(double width, double height) : width(width), height(height) {}

    const double direction{atan2(height, width)};

    const double radians{atan2(width, height)};

    const double distance{direction};

    /// 半角
    const double semiRadians{atan2(height, width / 2)};

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

DART_API struct Size Size_square(double dimension);

#pragma clang diagnostic pop

#endif //GRAPHICAL_SIZE_H
