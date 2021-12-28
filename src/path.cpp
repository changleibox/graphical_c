//
// Created by changlei on 2021/12/28.
//

#include "path.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Path Path_init(Incircle top, Incircle left, Incircle right) {
    return {top, left, right};
}

#pragma clang diagnostic pop
