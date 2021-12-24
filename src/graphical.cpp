#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
//
// Created by changlei on 2021/12/23.
//

#include <cmath>
#include <utility>
#include "graphical.h"

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic ignored "-Wreturn-stack-address"

struct Incircle {
public:
    const Offset center;

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
        Offset offset = Offset::zero();
        if (isinf(offsetHeight)) {
            size = Size(width, offsetHeight);
            offset = Offset(0, height - offsetHeight);
        }
        double radians = size.semiRadians();
        return Incircle::fromRadians(radians, radius).shift(offset);
    }

    /// 内切圆半径
    double radius() const {
        return abs((center - middle).distance());
    }

    /// 内切圆
    Rect circle() const {
        return Rect::fromCircle(center, radius());
    }

    /// 角的弧度
    double radians() const {
        return correctRadians(acos((begin - end).distance() / (2 * radius())));
    }

    /// 旋转的弧度
    double rotation() const {
        return correctRadians((end - begin).direction());
    }

    /// 角的顶点
    Offset vertex() const {
        double dy = radius() / sin(radians()) - radius();
        return {middle.dx + dy * sin(rotation()), middle.dy - dy * cos(rotation())};
    }

    /// 边界
    Rect bounds() const {
        initializer_list<double> dxs{begin.dx, middle.dx, end.dx};
        initializer_list<double> dys{begin.dy, middle.dy, end.dy};
        return {min(dxs), min(dys), max(dxs), max(dys)};
    }

    /// Returns a new [Incircle] translated by the given offset.
    ///
    /// To translate a rectangle by separate x and y components rather than by an
    /// [Offset], consider [translate].
    Incircle shift(Offset offset) const {
        return {begin + offset, middle + offset, end + offset};
    }

    /// 绕着Z轴顺时针旋转[radians]
    Incircle rotationX(double radians) const {
        return {begin.rotationX(radians), middle.rotationX(radians), end.rotationX(radians)};
    }

    /// 绕着Z轴顺时针旋转[radians]
    Incircle rotationY(double radians) const {
        return {begin.rotationY(radians), middle.rotationY(radians), end.rotationY(radians)};
    }

    /// 绕着Z轴顺时针旋转[radians]
    Incircle rotationZ(double radians) const {
        return {begin.rotationZ(radians), middle.rotationZ(radians), end.rotationZ(radians)};
    }

    /// 绕着角平分线旋转180度
    Incircle flipped() const {
        return {end, middle, begin};
    }

    /// 纠正[radians]，让它在[0, 360)之间
    static double correctRadians(double radians) {
        double newRadians = fmod(radians, radians360);
        return newRadians < 0 ? radians360 + newRadians : newRadians;
    }

    /// 修正因内切圆造成的位移
    static double offsetOf(Size size, double radius) {
        size = Size(size.width / 2, size.height - radius);
        double bof = size.radians();
        double boe = acos(radius / size.distance());
        return size.width / tan(bof + boe - radians90);
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
                .append("\"begin\":")
                .append("{" + begin.toJson() + "}")
                .append(",\"middle\":")
                .append("{" + middle.toJson() + "}")
                .append(",\"end\":")
                .append("{" + end.toJson() + "}")
                .append(",\"center\":")
                .append("{" + center.toJson() + "}")
                .append(",\"circle\":")
                .append("{" + circle().toJson() + "}")
                .append(",\"vertex\":")
                .append("{" + vertex().toJson() + "}")
                .append(",\"bounds\":")
                .append("{" + bounds().toJson() + "}")
                .append(",\"radius\":")
                .append(to_string(radius()))
                .append(",\"radians\":")
                .append(to_string(radians()))
                .append(",\"rotation\":")
                .append(to_string(rotation()));
    }


private:
    const Offset begin;
    const Offset middle;
    const Offset end;

    Incircle(Offset begin, Offset middle, Offset end) : begin(begin), middle(middle), end(end),
                                                        center(centerOf(begin, middle, end)) {}
};

struct Path {
public:
    const Incircle top;
    const Incircle left;
    const Incircle right;

    Path(Incircle top, Incircle left, Incircle right) : top(std::move(top)), left(std::move(left)),
                                                        right(std::move(right)) {}

    string toJson() const {
        return string()
                .append("{")
                .append("\"top\":")
                .append("{" + top.toJson() + "}")
                .append(",\"left\":")
                .append("{" + left.toJson() + "}")
                .append(",\"right\":")
                .append("{" + right.toJson() + "}")
                .append("}");
    }
};

/// 创建各个角
const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset) {
    const Size size = Size(width, height);
    const double topRadius = radius;
    const double leftRadius = blRadius == NAN ? radius : blRadius;
    const double rightRadius = brRadius == NAN ? radius : brRadius;

    const double topRadians = size.semiRadians();
    const Offset topOffset = Offset(width / 2, 0);
    const Incircle top = Incircle::fromSize(size, topRadius, avoidOffset).shift(topOffset);

    const double leftRadians = (radians90 + topRadians) / 2;
    const double leftRotation = radians90 + leftRadians;
    const Offset leftOffset = Offset(0, height);
    const Incircle left = Incircle::fromRadians(leftRadians, leftRadius).rotationZ(leftRotation).shift(leftOffset);

    const double rightRadians = (radians90 + topRadians) / 2;
    const double rightRotation = radians270 - leftRadians;
    const Offset rightOffset = Offset(width, height);
    const Incircle right = Incircle::fromRadians(rightRadians, rightRadius).rotationZ(rightRotation).shift(rightOffset);
    const Path path = {top, left, right};
    const string &json = path.toJson();
    char *str = new char[strlen(json.c_str()) + 1];
    return strcpy(str, json.c_str());
}

#pragma clang diagnostic pop