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

struct Size Size_square(double dimension) {
    return {dimension, dimension};
}

#pragma clang diagnostic pop
