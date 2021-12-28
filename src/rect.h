//
// Created by changlei on 2021/12/28.
//

#ifndef GRAPHICAL_RECT_H
#define GRAPHICAL_RECT_H

#include "size.h"
#include "offset.h"

using namespace std;

struct Rect {
public:
    const double left;
    const double top;
    const double right;
    const double bottom;

    Rect(double left, double top, double right, double bottom) : left(left), top(top), right(right), bottom(bottom) {}

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
               bottom == rhs.bottom &&
               size == rhs.size;
    }

    bool operator!=(const Rect &rhs) const {
        return !(rhs == *this);
    }
};


#endif //GRAPHICAL_RECT_H
