#ifndef HG_RATIONAL_H
#define HG_RATIONAL_H

#include <iostream>
#include <cstdint>
#include <string>
#include <ostream>

#include "nod.h"

class Rational {
public:
    Rational();
    Rational(const int32_t num);
    Rational(const int32_t num, const int32_t denum);

    bool operator== (const Rational s) const;
    bool operator!= (const Rational s) const;
    Rational operator+ (const Rational s) const;
    Rational operator- (const Rational s) const;
    Rational operator* (const Rational s) const;
    Rational operator/ (const Rational s) const;
    Rational& operator= (const Rational& s);
    void normalize();
    double toDouble() const;
    std::string toString() const;
    std::ostream& writeTo(std::ostream& os) const;
private:
    int32_t num_ = 0;
    int32_t denum_ = 1; 
};

inline std::ostream& operator<<(std::ostream& os, const Rational r){
    return r.writeTo(os);
}

#endif
