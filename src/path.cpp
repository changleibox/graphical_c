//
// Created by changlei on 2021/12/28.
//

#include "path.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Path Path_init(incircle top, incircle left, incircle right) {
    return {top, left, right};
}

const char *Path_toJson(Path path) {
    const string &json = path.toJson();
    char *str = new char[strlen(json.c_str()) + 1];
    return strcpy(str, json.c_str());
}

#pragma clang diagnostic pop
