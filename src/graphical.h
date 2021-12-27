//
// Created by changlei on 2021/12/23.
//

#include <string>
#include <cmath>
#include <vector>
#include <sstream>

#ifndef GRAPHICAL_GRAPHICAL_H
#define GRAPHICAL_GRAPHICAL_H

using namespace std;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

/// 180度对应的弧度
const double r180 = M_PI;

/// 90度对应的弧度
const double r90 = r180 / 2;

/// 90度对应的弧度
const double r270 = r180 * 3 / 2;

/// 360度对应的弧度
const double r360 = r180 * 2;

extern "C" {

struct Offset {
public:
    const double dx;
    const double dy;

    Offset(double dx, double dy) : dx(dx), dy(dy) {}

    /// The magnitude of the offset.
    ///
    /// If you need this value to compare it to another [Offset]'s distance,
    /// consider using [distanceSquared] instead, since it is cheaper to compute.
    const double distance{sqrt(dx * dx + dy * dy)};

    const double direction{atan2(dy, dx)};

    /// 绕X轴旋转
    Offset rotationX(double radians) const {
        return {dx, dy * cos(radians)};
    }

    /// 绕Y轴旋转
    Offset rotationY(double radians) const {
        return {dx * cos(radians), dy};
    }

    /// 绕Z轴旋转
    Offset rotationZ(double radians) const {
        double newCos = cos(radians);
        double newSin = sin(radians);
        return {dx * newCos - dy * newSin, dy * newCos + dx * newSin};
    }

    Offset operator+(const Offset &other) const {
        return {dx + other.dx, dy + other.dy};
    }

    Offset operator-(const Offset &other) const {
        return {dx - other.dx, dy - other.dy};
    }

    string toJson() const {
        return string()
                .append("\"dx\":")
                .append(to_string(dx))
                .append(",\"dy\":")
                .append(to_string(dy));
    }

    bool operator==(const Offset &rhs) const {
        return dx == rhs.dx &&
               dy == rhs.dy &&
               distance == rhs.distance &&
               direction == rhs.direction;
    }

    bool operator!=(const Offset &rhs) const {
        return !(rhs == *this);
    }
};

struct Size {
public:
    const double width;
    const double height;

    Size(double width, double height) : width(width), height(height) {}

    const double direction{atan2(height, width)};

    const double radians{atan2(width, height)};

    const double distance{direction};

    /// 半角
    const double semiRadians{atan2(height, width / 2)};

    string toJson() const {
        return string()
                .append("\"width\":")
                .append(to_string(width))
                .append(",\"height\":")
                .append(to_string(height))
                .append(",\"direction\":")
                .append(to_string(direction))
                .append(",\"radians\":")
                .append(to_string(radians))
                .append(",\"distance\":")
                .append(to_string(distance));
    }

    bool operator==(const Size &rhs) const {
        return width == rhs.width &&
               height == rhs.height &&
               direction == rhs.direction &&
               radians == rhs.radians &&
               distance == rhs.distance &&
               semiRadians == rhs.semiRadians;
    }

    bool operator!=(const Size &rhs) const {
        return !(rhs == *this);
    }
};

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
                .append("\"left\":")
                .append(to_string(left))
                .append(",\"top\":")
                .append(to_string(top))
                .append(",\"right\":")
                .append(to_string(right))
                .append(",\"bottom\":")
                .append(to_string(bottom))
                .append(",\"size\":")
                .append("{" + size.toJson() + "}");
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
                .append("\"begin\":")
                .append("{" + begin.toJson() + "}")
                .append(",\"middle\":")
                .append("{" + middle.toJson() + "}")
                .append(",\"end\":")
                .append("{" + end.toJson() + "}")
                .append(",\"center\":")
                .append("{" + center.toJson() + "}")
                .append(",\"circle\":")
                .append("{" + circle.toJson() + "}")
                .append(",\"vertex\":")
                .append("{" + vertex.toJson() + "}")
                .append(",\"bounds\":")
                .append("{" + bounds.toJson() + "}")
                .append(",\"radius\":")
                .append(to_string(radius))
                .append(",\"radians\":")
                .append(to_string(radians))
                .append(",\"rotation\":")
                .append(to_string(rotation));
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
                .append("{" + top.toJson() + "}")
                .append(",\"left\":")
                .append("{" + left.toJson() + "}")
                .append(",\"right\":")
                .append("{" + right.toJson() + "}")
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

Incircle fromRadians(double radians, double radius);

Incircle fromSize(double width, double height, double radius, bool avoidOffset = false);

const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset);

double pi();

double radians90();

double radians180();

double radians270();

double radians360();

}

#pragma clang diagnostic pop

#endif //GRAPHICAL_GRAPHICAL_H