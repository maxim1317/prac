#include "vec2d.h"

Vec2d::Vec2d(const double x_, const double y_){
    x = x_;
    y = y_;
}

Vec2d::Vec2d(const double b_x, const double b_y, const double e_x, const double e_y){
    x = e_x - b_x;
    y = e_y - b_y;
}

bool Vec2d::operator== (const Vec2d v) const {
    return(fabs(x - v.x) <= EPSILON && fabs(y - v.y) <= EPSILON);
}
bool Vec2d::operator!= (const Vec2d v) const {
    return(!operator==(v));
}

Vec2d Vec2d::operator+ (const Vec2d& v) const {
    return Vec2d(x + v.x, y + v.y);
}
Vec2d Vec2d::operator- (const Vec2d& v) const {
    return Vec2d(x - v.x, y - v.y);
}
Vec2d Vec2d::operator* (const double& d) const {
    return Vec2d(x * d, y * d);
}
Vec2d Vec2d::operator* (const Vec2d& v) const {
    return Vec2d(x * v.x, y * v.y);
}

double Vec2d::operator[] (const int ind) const {
    if (ind == 0){
        return x;
    } else if(ind == 1){
        return y;
    }
}

std::string Vec2d::toString() const {
    std::string str = "";
    str += std::to_string(x);
    str += ", ";
    str += std::to_string(y);
    return str;
}

std::ostream& Vec2d::writeTo(std::ostream& os) const{
    os << "(" << x << ", " << y << ")";
}

double Vec2d::length() const{
    return(sqrt((x * x) + (y * y)));
}