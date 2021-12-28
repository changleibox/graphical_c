//
// Created by changlei on 2021/12/28.
//

#ifndef GRAPHICAL_INCIRCLE_H
#define GRAPHICAL_INCIRCLE_H

#include <cmath>
#include "size.h"
#include "offset.h"
#include "rect.h"
#include "graphical.h"

using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct Incircle {
public:
    const struct Offset begin;
    const struct Offset middle;
    const struct Offset end;
    const struct Offset center;

    /// 根据一个角度和角内切圆的半径构建一个[Incircle]，[radians]为角对应的弧度，[radius]内切圆半径
    static Incircle fromRadians(double radians, double radius) {
        double eg = radius * cos(radians);
        double ai = radius / sin(radians) - radius;
        double ag = ai + radius - radius * sin(radians);

        return {Offset(-eg, ag), Offset(0, ai), Offset(eg, ag)};
    }

    /// 根据一个角度和角内切圆的半径构建一个[Incircle]，以[size]作为等腰三角形的底和高计算顶角的弧度，[radius]内切圆半径
    static Incircle fromSize(Size size, double radius, bool avoidOffset = false) {
        double width = size.width;
        double height = size.height;
        double offsetHeight = height;
        if (avoidOffset) {
            offsetHeight = Incircle::offsetOf(size, radius);
        }
        if (isinf(offsetHeight)) {
            const Size newSize(width, offsetHeight);
            const Offset offset(0, height - offsetHeight);
            double radians = newSize.semiRadians;
            return Incircle::fromRadians(radians, radius).shift(offset);
        } else {
            double radians = size.semiRadians;
            return Incircle::fromRadians(radians, radius);
        }
    }

    /// 内切圆半径
    const double radius{abs((center - middle).distance)};

    /// 内切圆
    const Rect circle{Rect::fromCircle(center, radius)};

    /// 角的弧度
    const double radians{correctRadians(acos((begin - end).distance / (2 * radius)))};

    /// 旋转的弧度
    const double rotation{correctRadians((end - begin).direction)};

    /// 角的顶点
    const Offset vertex{Offset(middle.dx + (radius / sin(radians) - radius) * sin(rotation), middle.dy - (radius / sin(radians) - radius) * cos(rotation))};

    /// 边界
    const Rect bounds{Rect(dxs().first, dys().first, dxs().second, dys().second)};

    /// Returns a new [Incircle] translated by the given offset.
    ///
    /// To translate a rectangle by separate x and y components rather than by an
    /// [Offset], consider [translate].
    Incircle shift(Offset offset) const {
        return {begin + offset, middle + offset, end + offset};
    }

    /// 绕着Z轴顺时针旋转[newRadians]
    Incircle rotationX(double newRadians) const {
        return {begin.rotationX(newRadians), middle.rotationX(newRadians), end.rotationX(newRadians)};
    }

    /// 绕着Z轴顺时针旋转[newRadians]
    Incircle rotationY(double newRadians) const {
        return {begin.rotationY(newRadians), middle.rotationY(newRadians), end.rotationY(newRadians)};
    }

    /// 绕着Z轴顺时针旋转[newRadians]
    Incircle rotationZ(double newRadians) const {
        return {begin.rotationZ(newRadians), middle.rotationZ(newRadians), end.rotationZ(newRadians)};
    }

    /// 绕着角平分线旋转180度
    Incircle flipped() const {
        return {end, middle, begin};
    }

    /// 纠正[radians]，让它在[0, 360)之间
    static double correctRadians(double radians) {
        double newRadians = fmod(radians, r360);
        return newRadians < 0 ? r360 + newRadians : newRadians;
    }

    /// 修正因内切圆造成的位移
    static double offsetOf(Size size, double radius) {
        const Size newSize(size.width / 2, size.height - radius);
        double bof = newSize.radians;
        double boe = acos(radius / newSize.distance);
        return newSize.width / tan(bof + boe - r90);
    }

    /// 根据圆上三个点计算圆心
    static Offset centerOf(Offset point1, Offset point2, Offset point3) {
        double x1 = point1.dx;
        double y1 = point1.dy;
        double x2 = point2.dx;
        double y2 = point2.dy;
        double x3 = point3.dx;
        double y3 = point3.dy;

        double a = 2 * (x2 - x1);
        double b = 2 * (y2 - y1);
        double c = pow(x2, 2) + pow(y2, 2) - pow(x1, 2) - pow(y1, 2);
        double d = 2 * (x3 - x2);
        double e = 2 * (y3 - y2);
        double f = pow(x3, 2) + pow(y3, 2) - pow(x2, 2) - pow(y2, 2);
        double dx = (b * f - e * c) / (b * d - e * a);
        double dy = (d * c - a * f) / (b * d - e * a);
        return {dx, dy};
    }

    string toJson() const {
        return string()
                .append("{")
                .append("\"begin\":")
                .append(begin.toJson())
                .append(",\"middle\":")
                .append(middle.toJson())
                .append(",\"end\":")
                .append(end.toJson())
                .append(",\"center\":")
                .append(center.toJson())
                .append(",\"circle\":")
                .append(circle.toJson())
                .append(",\"vertex\":")
                .append(vertex.toJson())
                .append(",\"bounds\":")
                .append(bounds.toJson())
                .append(",\"radius\":")
                .append(to_string(radius))
                .append(",\"radians\":")
                .append(to_string(radians))
                .append(",\"rotation\":")
                .append(to_string(rotation))
                .append("}");
    }


private:
    Incircle(Offset begin, Offset middle, Offset end) : begin(begin), middle(middle), end(end), center(centerOf(begin, middle, end)) {}

    pair<double, double> dxs() const {
        initializer_list<double> dxs{begin.dx, middle.dx, end.dx};
        return make_pair(min(dxs), max(dxs));
    }

    pair<double, double> dys() const {
        initializer_list<double> dys{begin.dy, middle.dy, end.dy};
        return make_pair(min(dys), max(dys));
    }

public:
    bool operator==(const Incircle &rhs) const {
        return begin == rhs.begin &&
               middle == rhs.middle &&
               end == rhs.end &&
               center == rhs.center &&
               radius == rhs.radius &&
               circle == rhs.circle &&
               radians == rhs.radians &&
               rotation == rhs.rotation &&
               vertex == rhs.vertex &&
               bounds == rhs.bounds;
    }

    bool operator!=(const Incircle &rhs) const {
        return !(rhs == *this);
    }
};

DART_API struct Incircle Incircle_fromRadians(double radians, double radius);

DART_API struct Incircle Incircle_fromSize(double width, double height, double radius, bool avoidOffset = false);

DART_API struct Incircle Incircle_shift(Incircle incircle, double dx, double dy);

DART_API struct Incircle Incircle_rotationX(Incircle incircle, double newRadians);

DART_API struct Incircle Incircle_rotationY(Incircle incircle, double newRadians);

DART_API struct Incircle Incircle_rotationZ(Incircle incircle, double newRadians);

DART_API struct Incircle Incircle_flipped(Incircle incircle);

DART_API const char *Incircle_toJson(Incircle incircle);

DART_API double Incircle_correctRadians(double radians);

DART_API double Incircle_offsetOf(Size size, double radius);

DART_API Offset Incircle_centerOf(Offset point1, Offset point2, Offset point3);

#pragma clang diagnostic pop

#endif //GRAPHICAL_INCIRCLE_H
