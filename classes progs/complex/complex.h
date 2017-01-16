#ifndef HG_COMPLEX_H
#define HG_COMPLEX_H

#include <string>
#include <cmath>
#include <ostream>

struct Complex  {
    double re = 0.0;
    double im = 0.0;
    const double EPSILON = 0.000000000001;

    Complex();
    Complex(const double real);
    Complex(const double real, const double img);
    bool operator==(const Complex c) const;
    bool operator!= (const Complex c) const;
    Complex operator+ (const Complex c) const;
    Complex operator- (const Complex c) const;
    Complex operator* (const Complex c) const;
    Complex operator/ (const Complex c) const;
    std::string toString() const;
    std::ostream& writeTo(std::ostream& ostrm) const;
    Complex& operator= (Complex& c) = default;
};

inline std::ostream& operator<< (std::ostream& os, const Complex& c){
    return c.writeTo(os);
}

#endif