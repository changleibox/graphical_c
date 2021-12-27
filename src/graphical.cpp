//
// Created by changlei on 2021/12/23.
//

#include <cmath>
#include <utility>
#include "graphical.h"

using namespace std;

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
};

struct Incircle {
public:
    const Offset begin;
    const Offset middle;
    const Offset end;
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
        double newRadians = fmod(radians, radians360);
        return newRadians < 0 ? radians360 + newRadians : newRadians;
    }

    /// 修正因内切圆造成的位移
    static double offsetOf(Size size, double radius) {
        const Size newSize(size.width / 2, size.height - radius);
        double bof = newSize.radians;
        double boe = acos(radius / newSize.distance);
        return newSize.width / tan(bof + boe - radians90);
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
};

struct Path {
public:
    const Incircle top;
    const Incircle left;
    const Incircle right;

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
};

/// 创建各个角
const char *cornerPath(double width, double height, double radius, double blRadius, double brRadius, bool avoidOffset) {
    const Size size = Size(width, height);
    const double topRadius = radius;
    const double leftRadius = blRadius == NAN ? radius : blRadius;
    const double rightRadius = brRadius == NAN ? radius : brRadius;

    const double topRadians = size.semiRadians;
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