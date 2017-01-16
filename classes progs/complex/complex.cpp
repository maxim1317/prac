#include "complex.h"

Complex::Complex() : Complex(0.0, 0.0){}
Complex::Complex(const double real): Complex(real, 0.0){}
Complex::Complex(const double real, const double img) : re(real), im(img){}

bool Complex::operator== (const Complex c) const {
    if (fabs(re - c.re) <= EPSILON && fabs(im - c.im) <= EPSILON){
        return true;
    } else {
        return false;
    }
}
bool Complex::operator!= (const Complex c) const {
    return (!operator==(c));
}

Complex Complex::operator+ (const Complex c) const {
    return Complex(re + c.re, im + c.im);
}
Complex Complex::operator- (const Complex c) const {
    return Complex(re - c.re, im - c.im);
}
Complex Complex::operator* (const Complex c) const {
    return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
}
Complex Complex::operator/ (const Complex c) const {
    double zn = c.re * c.re + c.im * c.im;
    return Complex((re * c.re + im * c.im) / zn, (im * c.re - re * c.im) / zn);
}

std::string Complex::toString() const {
    std::string res = "";
    res = std::to_string(re);
    res += " + ";
    res += std::to_string(im);
    res += "i";
    return res;
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const {
    ostrm << re;
    ostrm << " + i*";
    ostrm << im;
    return ostrm;
}