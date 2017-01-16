#ifndef HG_VEC2D_H
#define HG_VEC2D_H

#include <iostream>
#include <string>
#include <cmath>
#include <ostream>

class Vec2d {
public:
    Vec2d();
    Vec2d(const double x_, const double y_);
    Vec2d(const double b_x, const double b_y, const double e_x, const double e_y);
    
    bool operator== (const Vec2d v) const;
    bool operator!= (const Vec2d v) const;

    Vec2d operator+ (const Vec2d& v) const;
    Vec2d operator- (const Vec2d& v) const;
    Vec2d operator* (const double& d) const;
    Vec2d operator* (const Vec2d& v) const;
    Vec2d& operator= (const Vec2d& v) = default;

    double operator[] (const int ind) const;

    std::string toString() const;
    std::ostream& writeTo(std::ostream& os) const;
    double length() const;
private:
    double x = 0.0;
    double y = 0.0;
    const double EPSILON = 0.000000000001;
};

inline std::ostream& operator<<(std::ostream& os, const Vec2d v){
    return v.writeTo(os);
}

#endif