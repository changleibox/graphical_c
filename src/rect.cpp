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

#pragma clang diagnostic pop
