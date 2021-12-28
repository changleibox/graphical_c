//
// Created by changlei on 2021/12/28.
//

#ifndef GRAPHICAL_PATH_H
#define GRAPHICAL_PATH_H

#include <string>
#include "Incircle.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"

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

DART_API struct Path Path_init(Incircle top, Incircle left, Incircle right);

DART_API const char *Path_toJson(Path path);

#pragma clang diagnostic pop

#endif //GRAPHICAL_PATH_H
