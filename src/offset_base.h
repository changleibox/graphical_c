//
// Created by changlei on 2021/12/28.
//

#pragma once

#ifndef GRAPHICAL_OFFSET_BASE_H
#define GRAPHICAL_OFFSET_BASE_H


#include <cfloat>
#include <cmath>
#include <ostream>

struct OffsetBase {
public:
    OffsetBase(double dx, double dy) : _dx(dx), _dy(dy) {}

    bool isInfinite() const {
        return _dx >= DBL_MAX || _dy >= DBL_MAX;
    }

    bool isFinite() const {
        return !isinf(_dx) && !isinf(_dy);
    }

    bool operator<(OffsetBase other) const {
        return _dx < other._dx && _dy < other._dy;
    }

    bool operator<=(OffsetBase other) const {
        return _dx <= other._dx && _dy <= other._dy;
    }

    bool operator>(OffsetBase other) const {
        return _dx > other._dx && _dy > other._dy;
    }

    bool operator>=(OffsetBase other) const {
        return _dx >= other._dx && _dy >= other._dy;
    }

    friend std::ostream &operator<<(std::ostream &os, const OffsetBase &base) {
        os << "dx: " << base._dx << " dy: " << base._dy;
        return os;
    }

protected:
    const double _dx;
    const double _dy;
};


#endif //GRAPHICAL_OFFSET_BASE_H
