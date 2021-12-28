//
// Created by changlei on 2021/12/28.
//

#include "offset.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Offset Offset_init(double dx, double dy) {
    return {dx, dy};
}

#pragma clang diagnostic pop